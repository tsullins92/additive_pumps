#include "FrmMainApplication.h"
#include "EditRecipeWindow.h"
#include "FrmMain.h"
#include <iostream>
#include <gtkmm.h>
#include <gtkmm/dialog.h>

FrmMainApplication::FrmMainApplication()
: Gtk::Application("Additive Pumps")
{
  Glib::set_application_name("Additives");
}

Glib::RefPtr<FrmMainApplication> FrmMainApplication::create()
{
  return Glib::RefPtr<FrmMainApplication>(new FrmMainApplication());
}

void FrmMainApplication::on_startup()
{
  //Call the base class's implementation:
  Gtk::Application::on_startup();

  //Create actions for menus and toolbars.
  //We can use add_action() because Gtk::Application derives from Gio::ActionMap.

  //File|New sub menu:
  add_action("newrecipe",
    sigc::mem_fun(*this, &FrmMainApplication::on_menu_file_new_generic));
  
  //File menu:
  add_action("quit", sigc::mem_fun(*this, &FrmMainApplication::on_menu_file_quit));

  //Edit menu:
  add_action("editrecipe",
    sigc::mem_fun(*this, &FrmMainApplication::on_menu_edit_recipe));

  //Help menu:
  add_action("about", sigc::mem_fun(*this, &FrmMainApplication::on_menu_help_about));

  m_refBuilder = Gtk::Builder::create();

  //Layout the actions in a menubar and an application menu:
  Glib::ustring ui_info =
    "<interface>"
    "  <!-- menubar -->"
    "  <menu id='menubar'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Recipe</attribute>"
    "          <attribute name='action'>app.newrecipe</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
    "          <attribute name='action'>app.quit</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Edit</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Edit _Recipe</attribute>"
    "          <attribute name='action'>app.editrecipe</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;c</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Help</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_About</attribute>"
    "          <attribute name='action'>app.about</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
    ""
    "  <!-- application menu -->"
    "  <menu id='appmenu'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Recipe</attribute>"
    "          <attribute name='action'>app.newrecipe</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
    "          <attribute name='action'>app.quit</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Help</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_About</attribute>"
    "          <attribute name='action'>app.about</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Building menus failed: " << ex.what();
  }

  //Get the menubar and the app menu, and add them to the application:
  auto object = m_refBuilder->get_object("menubar");
  auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  object = m_refBuilder->get_object("appmenu");
  auto appMenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  if (!(gmenu && appMenu)) {
    g_warning("GMenu or AppMenu not found");
  }
  else
  {
    set_app_menu(appMenu);
    set_menubar(gmenu);
  }
}

void FrmMainApplication::on_activate()
{
  //std::cout << "debug1: " << G_STRFUNC << std::endl;
  // The application has been started, so let's show a window.
  // A real application might want to reuse this window in on_open(),
  // when asked to open a file, if no changes have been made yet.
  create_window();
}

void FrmMainApplication::create_window()
{
  auto win = new FrmMain();

  //Make sure that the application runs for as long this window is still open:
  add_window(*win);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  win->signal_hide().connect(sigc::bind<Gtk::Window*>(
    sigc::mem_fun(*this, &FrmMainApplication::on_window_hide), win));

  win->show_all();
}

void FrmMainApplication::on_window_hide(Gtk::Window* window)
{
  delete window;
}

void FrmMainApplication::on_menu_file_new_generic()
{
  std::cout << "A File|New menu item was selected." << std::endl;
}

void FrmMainApplication::on_menu_edit_recipe()
{
    EditRecipeWindow dialog();
    //dialog.run();
    return;
}

void FrmMainApplication::on_menu_file_quit()
{
    std::cout << G_STRFUNC << std::endl;
    quit(); // Not really necessary, when Gtk::Widget::hide() is called.

  // Gio::Application::quit() will make Gio::Application::run() return,
  // but it's a crude way of ending the program. The window is not removed
  // from the application. Neither the window's nor the application's
  // destructors will be called, because there will be remaining reference
  // counts in both of them. If we want the destructors to be called, we
  // must remove the window from the application. One way of doing this
  // is to hide the window.
    std::vector<Gtk::Window*> windows = get_windows();
    if (windows.size() > 0)
    {
        for(int i=0;i<windows.size()-1;++i)
              windows[i]->hide(); // Destroy each window
    }
}

void FrmMainApplication::on_menu_help_about()
{
  std::cout << "App|Help|About was selected." << std::endl;
}