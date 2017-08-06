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

#ifndef EDITRECIPEWINDOW_H
#define EDITRECIPEWINDOW_H
#include <gtkmm.h>
#include "CSVRow.h"
class EditRecipeWindow : public Gtk::Window
{
   protected:
	Gtk::Button m_BtnSave;
	Gtk::Button m_BtnCancel;
        Gtk::Label m_LblRecipe;
	Gtk::Label m_LblPump1;
        Gtk::Label m_LblPump2;
        Gtk::Label m_LblPump3;
        Gtk::Label m_LblPump4;
        Gtk::Label m_LblPump5;
        Gtk::Label m_LblPump6;
        Gtk::Label m_LblPump7;
        Gtk::Label m_LblPump8;
        Gtk::Label m_LblPump9;
        Gtk::Label m_LblPump10;
        Gtk::Entry m_EntryPump1;
        Gtk::Entry m_EntryPump2;
        Gtk::Entry m_EntryPump3;
        Gtk::Entry m_EntryPump4;
        Gtk::Entry m_EntryPump5;
        Gtk::Entry m_EntryPump6;
        Gtk::Entry m_EntryPump7;
        Gtk::Entry m_EntryPump8;
        Gtk::Entry m_EntryPump9;
        Gtk::Entry m_EntryPump10;
        Gtk::Box m_VBox1;
        Gtk::Box m_HBox0;
        Gtk::Box m_HBox1;
        Gtk::Box m_HBox2;
        Gtk::Box m_HBox3;
        Gtk::Box m_HBox4;
        Gtk::Box m_HBox5;
        Gtk::Box m_HBox6;
        Gtk::Box m_HBox7;
        Gtk::Box m_HBox8;
        Gtk::Box m_HBox9;
        Gtk::Box m_HBox10;       
        Gtk::Box m_HBox11;      
        Gtk::ComboBoxText m_Combo;
        
        std::vector<std::string> m_pump_values;
        CSVRow m_CSVRow;
        //signal handlers
	void on_save_button_clicked();
	void on_cancel_button_clicked();
        void on_combo_changed();
public:
	EditRecipeWindow();//constructor       
        virtual ~EditRecipeWindow();//destructor
  
};



#endif /* EditRecipeWindow_H */

