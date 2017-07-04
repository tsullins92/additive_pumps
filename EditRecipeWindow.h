/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EditRecipeWindow.h
 * Author: tim
 *
 * Created on July 3, 2017, 6:58 PM
 */

#ifndef EditRecipeWindow_H
#define EditRecipeWindow_H
#include <gtkmm.h>

class EditRecipeWindow : public Gtk::Window
{
   protected:
	Gtk::Button m_BtnSave;
	Gtk::Button m_BtnCancel;
	Gtk::Label m_LblPump1;
        Gtk::Label m_LblPump2;
        Gtk::Entry m_EntryPump1;
        Gtk::Entry m_EntryPump2;
        Gtk::Box m_VBox1;
        Gtk::Box m_HBox1;
        Gtk::Box m_HBox2;
        Gtk::Box m_HBox3;
        //Gtk::Box hBox4;
                
        
        //signal handlers
	void on_save_button_clicked();
	void on_cancel_button_clicked();
        
public:
	EditRecipeWindow();//constructor       
        virtual ~EditRecipeWindow();//destructor
  
};



#endif /* EditRecipeWindow_H */

