#include <iostream>
#include <gtkmm.h>
#include "FrmMain.h"

using namespace std;
using namespace Gtk;

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  FrmMain FrmMain;

  //Shows the window and returns when it is closed.
  return app->run(FrmMain);
}
