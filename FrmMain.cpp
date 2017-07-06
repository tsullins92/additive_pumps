/*
 * FrmMain.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: tim
 */

#include "FrmMain.h"
#include "AsyncSerial.h"
#include "BufferedAsyncSerial.h"
#include "ScaleWorker.h"
#include <iostream>
#include <boost/thread.hpp>
#include <string>
#include <gtkmm.h>
#include <typeinfo>
#include <boost/asio.hpp>
using namespace std;
using namespace Gtk;


FrmMain::FrmMain()
      : //Initialize gui elements
        btnStart("Start"),          //btnStart displays "Start"   
        btnCancel("Cancel"),        //btnCancel displays "Cancel"
        lblRunStatus("Pumps Inactive"),        //labelSentStatus displays Satus of pumps
        lblMass("Not Reading"),     //lblMass displays mass from scale        
        vBox1(Gtk::ORIENTATION_VERTICAL),       
        hBox1(Gtk::ORIENTATION_HORIZONTAL),
        hBox2(Gtk::ORIENTATION_HORIZONTAL),
        hBox3(Gtk::ORIENTATION_HORIZONTAL),
        hBox4(Gtk::ORIENTATION_HORIZONTAL),
        m_Dispatcher(),
        m_ScaleWorker(),
        m_ScaleWorkerThread(nullptr),   
        m_ArduinoWorker(),
        m_ArduinoWorkerThread(nullptr)  
{       
        //more initializing and packing elements into window
        set_title("Additives");
        set_size_request(350,300);
        set_border_width(0);
        hBox1.pack_start(lblMass, Gtk::PACK_EXPAND_PADDING);    //pack mass reading into hBox1
        vBox1.pack_start(hBox1, Gtk::PACK_EXPAND_PADDING);      //pack hBox1    
        hBox2.pack_start(lblRunStatus, Gtk::PACK_EXPAND_PADDING); //pack run status into hBox2
        vBox1.pack_start(hBox2, Gtk::PACK_EXPAND_PADDING);      //pack hBox2
        hBox3.pack_start(btnStart, Gtk::PACK_EXPAND_PADDING);      //pack OK button into hBox3
        hBox3.pack_start(btnCancel, Gtk::PACK_EXPAND_PADDING);      //pack cancel button into hBox3
        vBox1.pack_start(hBox3, Gtk::PACK_EXPAND_PADDING);      //pack hbox3
        entryVolume.set_max_length(50);
        entryVolume.set_text("Enter Volume Here");
        entryVolume.select_region(0, entryVolume.get_text_length());
        hBox4.pack_start(entryVolume, Gtk::PACK_EXPAND_PADDING);
        vBox1.pack_start(hBox4, Gtk::PACK_EXPAND_PADDING);      //pack hbox4
        add(vBox1);
        
        //connect signals to handlers
        btnStart.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_start_button_clicked));
        btnCancel.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_cancel_button_clicked));
        
        // Connect the handler to the dispatcher.
        m_Dispatcher.connect(sigc::mem_fun(*this, &FrmMain::on_notification_from_scale_worker_thread));
        update_start_stop_buttons();
        
        show_all_children();  
}

FrmMain::~FrmMain()
{
    
}
//signal handlers
void FrmMain::on_start_button_clicked(){
    if (m_ScaleWorkerThread||m_ArduinoWorkerThread)
    {
        std::cout << "Can't start a worker thread while another one is running." << std::endl;
     }
    else
    {   
        try
        {           
            double target_volume = stod(entryVolume.get_text());
            m_ScaleWorker.set_target_volume(&target_volume);
            start_scale_timeout();
            start_arduino_timeout();
            update_start_stop_buttons();
            lblRunStatus.set_text("Pumps Running");
        }
        catch(boost::system::system_error& e)
        {
            cout<<"Error: "<<e.what()<<endl;
        }
        catch(std::exception& e)
        {
            cout<<"Error: "<<e.what()<<endl;
        }      
    }
}

void FrmMain::on_cancel_button_clicked(){
    if (!m_ScaleWorkerThread)
  {
    std::cout << "Can't stop a worker thread. None is running." << std::endl;
  }
  else
  {
   // Order the worker thread to stop.
    m_ScaleWorker.stop_work();    
    btnCancel.set_sensitive(false);
  }
    if (!m_ArduinoWorkerThread)
  {
    std::cout << "Can't stop a worker thread. None is running." << std::endl;
  }
  else
  {
   // Order the worker thread to stop.
    m_ArduinoWorker.stop_work();    
    btnCancel.set_sensitive(false);
  }
}

void FrmMain::update_start_stop_buttons()
{
  const bool thread_is_running = m_ScaleWorkerThread != nullptr;

  btnStart.set_sensitive(!thread_is_running);
  btnCancel.set_sensitive(thread_is_running);
}

void FrmMain::update_widgets()
{
  Glib::ustring scale_reading;
  m_ScaleWorker.get_data(&scale_reading);
  lblMass.set_text(scale_reading); 
}

void FrmMain::update_arduino()
{
    string pump_command;
    m_ScaleWorker.get_pump_data(&pump_command);
    m_ArduinoWorker.set_data(&pump_command);
}

bool FrmMain::start_arduino_timeout()
{
    if (!m_ArduinoWorkerThread)
    {        

        //serial connection to arduino
         m_ArduinoWorkerThread = new std::thread([this]{m_ArduinoWorker.do_work(this);});
             return true;                   
    } 
    else
    {
        return false;        
    }  
}

bool FrmMain::start_scale_timeout()
{   
    if (!m_ScaleWorkerThread)
    {        

        //serial connection to scale
         m_ScaleWorkerThread = new std::thread([this]{m_ScaleWorker.do_work(this);});
             return true;                   
    } 
    else
    {
        return false;        
    }  
}

void FrmMain::notify()
{
  m_Dispatcher.emit();
}

void FrmMain::on_notification_from_scale_worker_thread()
{
    if (m_ScaleWorkerThread && m_ScaleWorker.has_stopped())
  {
        //Work is done.
        if (m_ScaleWorkerThread->joinable())
           m_ScaleWorkerThread->join();
        delete m_ScaleWorkerThread;
        m_ScaleWorkerThread = nullptr;
        lblMass.set_text("Not Reading");
        lblRunStatus.set_text("Pumps Inactive");
        update_start_stop_buttons();
  }
    else
    {
        update_widgets();
        update_arduino();
    }
    if (m_ArduinoWorkerThread && m_ArduinoWorker.has_stopped())
    {
        if (m_ArduinoWorkerThread->joinable())
           m_ArduinoWorkerThread->join();
        delete m_ArduinoWorkerThread;
        m_ArduinoWorkerThread = nullptr;
    }
}
