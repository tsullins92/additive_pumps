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
#include <fcntl.h>
#include <termios.h>
#include <string.h> // needed for memset
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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
    struct termios tio;
    struct termios stdio;
    int tty_fd;
    fd_set rdset;

    memset(&stdio,0,sizeof(stdio));
    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;
    tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tty_fd=open("/dev/ttyACM0", O_RDWR | O_NONBLOCK);      
    cfsetospeed(&tio,B9600);            // 9600 baud
    cfsetispeed(&tio,B9600);            // 9600 baud

    tcsetattr(tty_fd,TCSANOW,&tio);
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_has_stopped = false;
    }
    for(;;)
    {    
        
        //sleep to give time for serial to buffer and main thread to perform set_data()
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
               
        {
            //lock the rest of the activity so that the main thread cannot interfere
            std::lock_guard<std::mutex> lock(m_Mutex);
            
            if (m_shall_stop)
            {
                char c = 'l';
                write(tty_fd,&c,1);
                break;           
            }
            
            const char *mycharp = m_pump_command.c_str();
            write(tty_fd,mycharp,2);       
            //cout<<"m_pump_command = "<<m_pump_command<<"\n";  
        }
    }
    close(tty_fd);
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
