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
  m_target_volume(0.0),
  m_pump_command("")      
{
}

// Accesses to these data are synchronized by a mutex.
// Some microseconds can be saved by getting all data at once, instead of having
// separate get_fraction_done() and get_message() methods.
void ScaleWorker::get_data(Glib::ustring* scale_reading) const
{
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (scale_reading)
    *scale_reading = m_scale_reading;
}

void ScaleWorker::get_pump_data(string* pump_command) const
{
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (pump_command)
    *pump_command = m_pump_command;
}

void ScaleWorker::set_target_volume(double* target_volume)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    if (target_volume)
        m_target_volume = *target_volume;
}

void ScaleWorker::do_work(FrmMain* caller)
{    
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
            
            if (m_shall_stop)
            {
                break;
            }
            string scaleReading = scaleSerial.readStringUntil("\r"); 
            
            if(!scaleReading.empty()){
                m_scale_reading = scaleReading;
            }
            
            cout<<"scaleReading = "<<scaleReading<<endl;  
            
            scaleSerial.close();
            try
            {            
                control_active_pumps(past_reading,m_scale_reading,m_target_volume); 
            } 
            catch(std::invalid_argument& e)
            {
                cout<<"Error: "<<e.what()<<endl;
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            past_reading = m_scale_reading;    
            }
        
        
        caller->notify();   
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_shall_stop = false;
    m_has_stopped = true;
    }
    caller->notify(); 
}



void ScaleWorker::control_active_pumps(string past_reading,string& scale_reading, double target_volume)
{
    stringstream ssin {scale_reading};
    stringstream ssout {""};
    double value;
    bool valid_reading = false;
    
    for (char ch;ssin.get(ch);)
    { 
        if(isdigit(ch))
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
    if(valid_reading)
    {
        value = stod(ssout.str());
        if (value<target_volume)
            m_pump_command = "h";
        else
            m_pump_command = "l";

        scale_reading = ssout.str();
        cout << "ssout = " << ssout.str() << "\n";
        cout <<"value = " << value << "\n";
        cout << "target_volume = " << target_volume << "\n";
        return;
    }
    else 
    {
        scale_reading = past_reading;
        return;
    }
}

void ScaleWorker::stop_work()
{
  std::lock_guard<std::mutex> lock(m_Mutex);
  m_shall_stop = true;
}

bool ScaleWorker::has_stopped() const
{
  std::lock_guard<std::mutex> lock(m_Mutex);
  return m_has_stopped;
}
