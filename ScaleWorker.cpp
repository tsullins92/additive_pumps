/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ScaleWorker.h"
#include "FrmMain.h"
#include <sstream>
#include <chrono>

ScaleWorker::ScaleWorker() :
  m_Mutex(),
  m_shall_stop(false),
  m_has_stopped(false),
  m_fraction_done(0.0),
  m_message()
{
}

// Accesses to these data are synchronized by a mutex.
// Some microseconds can be saved by getting all data at once, instead of having
// separate get_fraction_done() and get_message() methods.
void ScaleWorker::get_data(double* fraction_done, Glib::ustring* message) const
{
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (fraction_done)
    *fraction_done = m_fraction_done;

  if (message)
    *message = m_message;
}

bool ScaleWorker::start_serial_read(bool connection)
{   
    if (connection == true)
    {        
        try 
        {   //serial connection to scale
            BufferedAsyncSerial scaleSerial("/dev/ttyUSB0",9600); 
            sleep(1);
            //boost::this_thread::sleep(boost::posix_time::seconds(2));
            string scaleReading = scaleSerial.readStringUntil("\r"); 
            if(!scaleReading.empty()){
                lblMass.set_text(scaleReading);
            }
            cout<<"scaleReading = "<<scaleReading<<endl;  
            scaleSerial.close();
            control_active_pumps(scaleReading,"60");           
            sleep(0.5);
            //serial connection to arduino
            BufferedAsyncSerial pumpSerial("/dev/ttyACM0",9600,boost::asio::serial_port_base::parity(
                boost::asio::serial_port_base::parity::none),boost::asio::serial_port_base::character_size(8));
            sleep(1);
            string pumpReading = pumpSerial.readStringUntil("\r"); 
            cout<<"pumpReading = "<<pumpReading<<endl;
            pumpSerial.close();
            return true;
        }   
        catch(boost::system::system_error& e)
        {
        cout<<"Error: "<<e.what()<<endl;
        return true;
        }
        catch(std::exception& f){
            cout<<"Error: "<<f.what()<<endl;
        return true;
        }
    } 
    else
    {
        return false;        
    }  
}

void ScaleWorker::control_active_pumps(string reading, string target)
{
    stringstream ssin {reading};
    stringstream ssout;
    double value;
    double goal = stod(target);
    
    for (char ch;ssin.get(ch);){ 
        if((isdigit(ch))||ch=='.'){
            ssout<<ch;
        }          
    }
    cout << "ssout = " << ssout.str() << "\n";
    value = stod(ssout.str());
    cout <<"value = " << value << "\n";
    cout << "goal = " << goal << "\n";
    return;
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

void ScaleWorker::do_work(FrmMain* caller)
{
  {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_has_stopped = false;
    m_fraction_done = 0.0;
    m_message = "";
  } // The mutex is unlocked here by lock's destructor.

  // Simulate a long calculation.
  for (int i = 0; ; ++i) // do until break
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    {
      std::lock_guard<std::mutex> lock(m_Mutex);

      m_fraction_done += 0.01;

      if (i % 4 == 3)
      {
        std::ostringstream ostr;
        ostr << (m_fraction_done * 100.0) << "% done\n";
        m_message += ostr.str();
      }

      if (m_fraction_done >= 1.0)
      {
        m_message += "Finished";
        break;
      }
      if (m_shall_stop)
      {
        m_message += "Stopped";
        break;
      }
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