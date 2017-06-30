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
        timeout_value(3000), // 1500 ms = 1.5 seconds 
        connection(false),              //variable controlling connection to scale
        vBox1(Gtk::ORIENTATION_VERTICAL),       
        hBox1(Gtk::ORIENTATION_HORIZONTAL),
        hBox2(Gtk::ORIENTATION_HORIZONTAL),
        hBox3(Gtk::ORIENTATION_HORIZONTAL),
        hBox4(Gtk::ORIENTATION_HORIZONTAL),
        m_Dispatcher(),
        m_Worker(),
        m_WorkerThread(nullptr)   
{       
        //more initializing and packing elements into window
        set_title("Additives");
        //set_size_request(350,300);
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
        
//        m_refActionGroup = Gio::SimpleActionGroup::create();
//
//        m_refActionGroup->add_action("new", sigc::mem_fun(*this, &FrmMain::on_action_file_new));
//        m_refActionGroup->add_action("open", sigc::mem_fun(*this, &FrmMain::on_action_file_open));
//        m_refActionGroup->add_action("quit", sigc::mem_fun(*this, &FrmMain::on_action_file_quit));
//
//        insert_action_group("example", m_refActionGroup);

        
        //connect signals to handlers
        btnStart.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_start_button_clicked));
	btnCancel.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_cancel_button_clicked));
        
        // Connect the handler to the dispatcher.
        m_Dispatcher.connect(sigc::mem_fun(*this, &FrmMain::on_notification_from_worker_thread));
        update_start_stop_buttons();
        
        show_all_children();  
}

FrmMain::~FrmMain(){
    
}
//signal handlers
void FrmMain::on_start_button_clicked(){
    if (m_WorkerThread)
    {
        std::cout << "Can't start a worker thread while another one is running." << std::endl;
     }
    else
    {
        connection = true;
        double target_volume = stod(entryVolume.get_text());
        m_Worker.set_target_volume(&target_volume);
        start_scale_timeout(connection);
        update_start_stop_buttons();
        lblRunStatus.set_text("Pumps Running");
    }
}

void FrmMain::on_cancel_button_clicked(){
    if (!m_WorkerThread)
  {
    std::cout << "Can't stop a worker thread. None is running." << std::endl;
  }
  else
  {
   // Order the worker thread to stop.
    connection = false;
    conn.disconnect();
    lblMass.set_text("Not Reading");
    lblRunStatus.set_text("Pumps Inactive");
    m_Worker.stop_work();
    btnCancel.set_sensitive(false);
  }
}

void FrmMain::update_start_stop_buttons()
{
  const bool thread_is_running = m_WorkerThread != nullptr;

  btnStart.set_sensitive(!thread_is_running);
  btnCancel.set_sensitive(thread_is_running);
}

void FrmMain::update_widgets()
{
  Glib::ustring scale_reading;
  m_Worker.get_data(&scale_reading);
  lblMass.set_text(scale_reading); 
}

bool FrmMain::start_scale_timeout(bool connection)
{   
    if (connection && !m_WorkerThread)
    {        
        try 
        {   //serial connection to scale
            m_WorkerThread = new std::thread(
                [this]
                {
                  m_Worker.do_work(this);
                });
                return true;
        }   
        catch(boost::system::system_error& e)
        {
        cout<<"Error: "<<e.what()<<endl;
        return true;
        }
        
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

void FrmMain::on_notification_from_worker_thread()
{
//    if (m_WorkerThread && m_Worker.has_stopped())
//  {
//     //Work is done.
//    if (m_WorkerThread->joinable())
//        m_WorkerThread->join();
//    delete m_WorkerThread;
//    m_WorkerThread = nullptr;
//    update_start_stop_buttons();
//  }
  update_widgets();
}