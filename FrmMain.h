/*
 * FrmMain.h
 *
 *  Created on: Jun 17, 2017
 *      Author: tim
 */

#ifndef FRMMAIN_H_
#define FRMMAIN_H_


#include <gtkmm.h>
#include <iostream>
#include <termios.h>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <string>
#include <sigc++/sigc++.h>

class FrmMain : public Gtk::Window{
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Button *btnOk;
	Gtk::Button *btnCancel;
	Gtk::Label *labelSentStatus;
        Gtk::Label *lblMass;
        static std::string scaleReading;
        static std::string prevScaleReading;

public:
	FrmMain(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);//constructor
        typedef sigc::signal<void> type_scale_read;
        type_scale_read scale_read();


protected:
	//signal handlers
	void on_ok_button_clicked();
	void on_cancel_button_clicked();
        void FrmMain::on_scale_read()
        static void received(const char *data, unsigned int len);
        void start_serial_read(std::string dev,unsigned int baud);
};

#endif /* FRMMAIN_H_ */
