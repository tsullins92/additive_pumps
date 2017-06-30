#include <iostream>
#include <gtkmm.h>
#include "FrmMain.h"
#include "FrmMainApplication.h"

using namespace std;
using namespace Gtk;

int main (int argc, char *argv[])
{
  auto app = FrmMainApplication::create();
// Start the application, showing the initial window,
  // and opening extra windows for any files that it is asked to open,
  // for instance as a command-line parameter.
  // run() will return when the last window has been closed by the user.
  const int status = app->run(argc, argv);
  return status;
}
