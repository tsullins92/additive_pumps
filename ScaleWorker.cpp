/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ScaleWorker.h"
#include "FrmMain.h"
#include "BufferedAsyncSerial.h"
#include <sstream>
#include <chrono>

ScaleWorker::ScaleWorker() :
  m_Mutex(),
  m_shall_stop(false),
  m_has_stopped(false), 
  m_scale_reading("0.0"),
  m_pump_command("")      
{
}

// Accesses to these data are synchronized by a mutex.

//called by main thread to get mass reading from scale
void ScaleWorker::get_data(Glib::ustring* scale_reading) const
{
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (scale_reading)
    *scale_reading = m_scale_reading;
}


//called by main thread to get the command to send to the arduino thread
void ScaleWorker::get_pump_data(string* pump_command) const
{
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (pump_command)
    *pump_command = m_pump_command;
}


//called by main thread to set the target volumes of each of the pump sequences
void ScaleWorker::set_target_volume(std::vector<double>* target_volumes)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    if (target_volumes)
    {
        m_target_volumes = *target_volumes;
    }
    
}

//main loop of this thread. reads data in from scale, passes that data to 
//control_active_pumps(), and then calls notify. 
void ScaleWorker::do_work(FrmMain* caller)
{   
    m_current_pump = 0;
    m_stable_reading_counter = 0;
    string past_reading = "0.0";
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_has_stopped = false;
    }
    for(;;)
    {   
        //serial connection to scale
        BufferedAsyncSerial scaleSerial("/dev/ttyUSB0",9600);  
        //sleep to give time for serial to buffer and main thread to perform get_data()
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
               
        {
            //lock the rest of the activity so that the main thread cannot interfere
            std::lock_guard<std::mutex> lock(m_Mutex);
            
            if (m_shall_stop||(m_current_pump>9))
            {
                break;
            }
            string scaleReading = scaleSerial.readStringUntil("\r"); 
            //scaleSerial.close();
            
            if(!scaleReading.empty()){
                m_scale_reading = scaleReading;
            }
            
            cout<<"scaleReading = "<<scaleReading<<endl;  
            
            try
            {            
                control_active_pumps(past_reading,m_scale_reading,m_target_volumes[m_current_pump]); 
            } 
            catch(std::invalid_argument& e)
            {
                cout<<"Error: "<<e.what()<<endl;
            }

            
            past_reading = m_scale_reading;    
            }
        
        
        caller->notify();   

    }
    {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_shall_stop = false;
    m_has_stopped = true;
    }
    caller->notify(); 
}


//Gets scale reading from do_work() loop and decides whether the scale reading is 
//valid and which pump command to send.
void ScaleWorker::control_active_pumps(string past_reading,string& scale_reading, double target_volume)
{
    stringstream ssin {scale_reading};
    stringstream ssout {""};
    double value;
    double past_value;
    bool valid_reading = false;
    
    for (char ch;ssin.get(ch);)
    { 
        if(isdigit(ch)||ch=='-')
        {
            ssout<<ch;
        }
        else if(ch=='.')
        {
            ssout<<ch;
            valid_reading = true;
        }    
        else if(ch=='\r')
        {
            break;
        }    
    }
    past_value = stod(past_reading);
    if(valid_reading&&abs(past_value-stod(ssout.str()))<20.0)
    {
        value = stod(ssout.str());
        if (value<target_volume)
        {
            if((value>(target_volume-2.0)))
            {
                m_pump_command = ("m"+std::to_string(m_current_pump));  
            }
            else
            {
                m_pump_command = std::to_string(m_current_pump)+"h";
            }    
        }    
        else
        {
            m_pump_command = "l";
            ++m_stable_reading_counter;
            if (m_stable_reading_counter>3)  
                {
                    m_stable_reading_counter = 0;
                    ++m_current_pump;
                    m_target_volumes[m_current_pump] += value;
                }
        } 
        scale_reading = ssout.str();
        cout << "m_current_pump = " << m_current_pump << "\n";
        cout<<"m_pump_command = "<<m_pump_command<<"\n";  
        return;
    }
    else 
    {
        scale_reading = past_reading;
        return;
    }
}

//called my main thread. do_work() loop will call break when m_shall_stop is true
void ScaleWorker::stop_work()
{
  std::lock_guard<std::mutex> lock(m_Mutex);
  m_shall_stop = true;
}

//called  by main thread to check on status of the loop. main will join the threads and 
//delete the ScaleWorker object if this function returns a true value
bool ScaleWorker::has_stopped() const
{
  std::lock_guard<std::mutex> lock(m_Mutex);
  return m_has_stopped;
}
