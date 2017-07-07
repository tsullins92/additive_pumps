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
    char serialPortFilename[] = "/dev/ttyACM0";  
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_has_stopped = false;
    }
    for(;;)
    {    
        FILE *serPort = fopen(serialPortFilename, "w");
        if (serPort == NULL)
		{
			printf("ERROR");
		}
        //sleep to give time for serial to buffer and main thread to perform set_data()
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
               
        {
            //lock the rest of the activity so that the main thread cannot interfere
            std::lock_guard<std::mutex> lock(m_Mutex);
            
            if (m_shall_stop)
            {
                break;           
            }
            
            char msg[] = {m_pump_command[0]};
            fwrite(msg, sizeof(char), sizeof(msg), serPort); 
            cout<<"m_pump_command = "<<m_pump_command<<endl;  
            fclose(serPort);
        }
    }
    {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_shall_stop = false;
    m_has_stopped = true;
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
