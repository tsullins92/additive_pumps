/*
 * FrmMain.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: tim
 */

#include "FrmMain.h"
#include "AsyncSerial.h"
#include "BufferedAsyncSerial.h"
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
        hBox4(Gtk::ORIENTATION_HORIZONTAL)
         
{       
        //more initializing and packing elements into window
        set_title("Additives");
        set_border_width(10);
        hBox1.pack_start(lblMass, Gtk::PACK_SHRINK);    //pack mass reading into hBox1
        vBox1.pack_start(hBox1, Gtk::PACK_SHRINK);      //pack hBox1    
        hBox2.pack_start(lblRunStatus, Gtk::PACK_SHRINK); //pack run status into hBox2
        vBox1.pack_start(hBox2, Gtk::PACK_SHRINK);      //pack hBox2
        hBox3.pack_start(btnStart, Gtk::PACK_SHRINK);      //pack OK button into hBox3
        hBox3.pack_start(btnCancel, Gtk::PACK_SHRINK);      //pack cancel button into hBox3
        vBox1.pack_start(hBox3, Gtk::PACK_SHRINK);      //pack hbox3
        entryVolume.set_max_length(50);
        entryVolume.set_text("hello");
        entryVolume.set_text(entryVolume.get_text() + " world");
        entryVolume.select_region(0, entryVolume.get_text_length());
        hBox4.pack_start(entryVolume, Gtk::PACK_SHRINK);
        vBox1.pack_start(hBox4, Gtk::PACK_SHRINK);      //pack hbox4
        add(vBox1);
        
        //connect signals to handlers
        btnStart.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_start_button_clicked));
	btnCancel.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_cancel_button_clicked));
        
        // Connect the handler to the dispatcher.
        m_Dispatcher.connect(sigc::mem_fun(*this, &ExampleWindow::on_notification_from_worker_thread));
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
        sigc::slot<bool> timeoutSlot = sigc::bind<bool>(sigc::mem_fun(*this, &FrmMain::start_serial_read),connection);
        conn = Glib::signal_timeout().connect(timeoutSlot,timeout_value);
        lblRunStatus.set_text("Pumps Running");
    }
}

void FrmMain::on_cancel_button_clicked(){
	//labelSentStatus.set_text("");
    connection = false;
    conn.disconnect();
    lblMass.set_text("Not Reading");
    lblRunStatus.set_text("Pumps Inactive");
}

