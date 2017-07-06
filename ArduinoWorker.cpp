/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ArduinoWorker.h"
#include "FrmMain.h"
#include "BufferedAsyncSerial.h"
#include <sstream>
#include <chrono>

ArduinoWorker::ArduinoWorker() :
  m_Mutex(),
  m_shall_stop(false),
  m_has_stopped(false), 
  m_pump_command("l")      
{   
}

// Accesses to these data are synchronized by a mutex.
// Some microseconds can be saved by getting all data at once, instead of having
// separate get_fraction_done() and get_message() methods.
void ArduinoWorker::set_data(string* pump_command)
{
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (pump_command)
    m_pump_command = *pump_command;
}

void ArduinoWorker::do_work(FrmMain* caller)
{    
    BufferedAsyncSerial m_ArduinoSerial("/dev/ttyACM0",9600,boost::asio::serial_port_base::parity(
                boost::asio::serial_port_base::parity::none),boost::asio::serial_port_base::character_size(8)); 
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_has_stopped = false;
    }
    for(;;)
    {                 
        //sleep to give time for serial to buffer and main thread to perform set_data()
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
               
        {
            //lock the rest of the activity so that the main thread cannot interfere
            std::lock_guard<std::mutex> lock(m_Mutex);
            
            if (m_shall_stop)
            {
                break;           
            }
                
            m_ArduinoSerial.writeString(m_pump_command);
            
            string arduinoReading = m_ArduinoSerial.readStringUntil("\r"); 
            
            cout<<"arduinoReading = "<<arduinoReading<<endl;  
            
            //arduinoSerial.close();
        }
    }
    {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_shall_stop = false;
    m_has_stopped = true;
    m_ArduinoSerial.close();
    }
    caller->notify(); 
}

void ArduinoWorker::stop_work()
{
  std::lock_guard<std::mutex> lock(m_Mutex);
  m_shall_stop = true;
}

bool ArduinoWorker::has_stopped() const
{
  std::lock_guard<std::mutex> lock(m_Mutex);
  return m_has_stopped;
}
