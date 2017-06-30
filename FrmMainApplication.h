/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FrmMainApplication.h
 * Author: tim
 *
 * Created on June 30, 2017, 11:43 AM
 */

#ifndef FRMMAINAPPLICATION_H
#define FRMMAINAPPLICATION_H
#include <gtkmm.h>

class FrmMainApplication : public Gtk::Application
{
protected:
  FrmMainApplication();

public:
  static Glib::RefPtr<FrmMainApplication> create();

protected:
  //Overrides of default signal handlers:
  void on_startup() override;
  void on_activate() override;

private:
  void create_window();

  void on_window_hide(Gtk::Window* window);
  void on_menu_file_new_generic();
  void on_menu_edit_recipe();
  void on_menu_file_quit();
  void on_menu_help_about();

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
};


#endif /* FRMMAINAPPLICATION_H */

