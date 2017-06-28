/*
 * FrmMain.h
 *
 *  Created on: Jun 17, 2017
 *      Author: tim
 */

#ifndef FRMMAIN_H_
#define FRMMAIN_H_

#include "BufferedAsyncSerial.h"
#include "ScaleWorker.h"
#include <gtkmm.h>
#include <iostream>
#include <boost/thread.hpp>
#include <string>
#include <gtkmm.h>
using namespace std;

class FrmMain : public Gtk::Window{
protected:
	Gtk::Button btnStart;
	Gtk::Button btnCancel;
	Gtk::Label lblRunStatus;
        Gtk::Label lblMass;
        Gtk::Entry entryVolume;
        Gtk::Box vBox1;
        Gtk::Box hBox1;
        Gtk::Box hBox2;
        Gtk::Box hBox3;
        Gtk::Box hBox4;
        
        const int timeout_value;
        sigc::connection conn;
        bool connection;
        Glib::Dispatcher m_Dispatcher;
        ScaleWorker m_Worker;
        std::thread* m_WorkerThread;
        
        // Dispatcher handler.
        void on_notification_from_worker_thread();
        //signal handlers
	void on_start_button_clicked();
	void on_cancel_button_clicked();
        
        bool start_scale_timeout(bool connection);
        void update_start_stop_buttons();
        void update_widgets();
public:
	FrmMain();//constructor
        // Called from the worker thread.
        void notify();
        virtual ~FrmMain();//destructor
};

#endif /* FRMMAIN_H_ */
