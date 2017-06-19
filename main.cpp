#include <iostream>
#include <gtkmm.h>
#include "FrmMain.h"

using namespace std;
using namespace Gtk;

int main(int argc, char **argv) {
	cout << "Started" << endl;

	Main kit(argc,argv);
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("gui.glade");

	FrmMain *frm = 0;
	builder->get_widget_derived("frmMain", frm);
	kit.run(*frm);

	cout << "End" << endl;

	return 0;
}