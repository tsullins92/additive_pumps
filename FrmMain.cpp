/*
 * FrmMain.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: tim
 */

#include "FrmMain.h"

using namespace std;
using namespace Gtk;


FrmMain::FrmMain(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	:
	Gtk::Window(cobject),
	builder(refGlade)
{

	builder->get_widget("btnOk", btnOk);
	builder->get_widget("btnCancel", btnCancel);
	builder->get_widget("labelSentStatus",labelSentStatus);

	btnOk->signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_ok_button_clicked));
	btnCancel->signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_cancel_button_clicked));

}


void FrmMain::on_ok_button_clicked(){
	labelSentStatus->set_text("Sent");
}

void FrmMain::on_cancel_button_clicked(){
	labelSentStatus->set_text("");
}

