/*
 * FrmMain.h
 *
 *  Created on: Jun 17, 2017
 *      Author: tim
 */

#ifndef FRMMAIN_H_
#define FRMMAIN_H_


#include <gtkmm.h>

class FrmMain : public Gtk::Window{
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Button *btnOk;
	Gtk::Button *btnCancel;
	Gtk::Label *labelSentStatus;

public:
	FrmMain(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);//constructor

protected:
	//signal handlers
	void on_ok_button_clicked();
	void on_cancel_button_clicked();

};

#endif /* FRMMAIN_H_ */
