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
#include "ArduinoWorker.h"
#include "CSVRow.h"
#include <gtkmm.h>
#include <iostream>
#include <boost/thread.hpp>
#include <string>
#include <gtkmm.h>
using namespace std;

class FrmMain : public Gtk::ApplicationWindow{
protected:
	Gtk::Button btnStart;
	Gtk::Button btnCancel;
        Gtk::Label lblRunStatus1;
	Gtk::Label lblRunStatus2;
        Gtk::Label lblMass1;
        Gtk::Label lblMass2;
        Gtk::Entry entryVolume;
        Gtk::Box vBox1;
        Gtk::Box hBox1;
        Gtk::Box hBox2;
        Gtk::Box hBox3;
        Gtk::Box hBox4;
        Gtk::ComboBoxText m_Combo;
        //Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
        
        Glib::Dispatcher m_Dispatcher;
        ScaleWorker m_ScaleWorker;
        ArduinoWorker m_ArduinoWorker;
        std::thread* m_ArduinoWorkerThread;
        std::thread* m_ScaleWorkerThread;
        std::vector<std::string> m_pump_values;
        std::vector<double> m_pump_sequence_vector;
        CSVRow m_CSVRow;
        // Dispatcher handler.
        void on_notification_from_scale_worker_thread();
        //signal handlers
	void on_start_button_clicked();
	void on_cancel_button_clicked();
        void on_combo_changed();
        
        bool start_scale_timeout();
        bool start_arduino_timeout();
        void update_start_stop_buttons();
        void update_widgets();
        void update_arduino();
        
public:
	FrmMain();//constructor
        // Called from the worker thread.
        void notify();
        virtual ~FrmMain();//destructor
};

#endif /* FRMMAIN_H_ */
