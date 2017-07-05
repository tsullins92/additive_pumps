/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "EditRecipeWindow.h"
#include <gtkmm.h>
#include <iostream>

using namespace std;
using namespace Gtk;


EditRecipeWindow::EditRecipeWindow()
      : //Initialize gui elements
        m_BtnSave("Save"),          //m_BtnSave displays "Save"   
        m_BtnCancel("Cancel"),        //m_BtnCancel displays "Cancel"
        m_LblPump1("Pump 1: "),
        m_LblPump2("Pump 2: "),
        m_VBox1(Gtk::ORIENTATION_VERTICAL),       
        m_HBox1(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox2(Gtk::ORIENTATION_HORIZONTAL)
{       
        //more initializing and packing elements into window
        set_title("Edit Recipes");
        //set_size_request(350,300);
        set_border_width(0);
        m_EntryPump1.set_text("mL/L");
        m_EntryPump2.set_text("mL/L");
        m_HBox1.pack_start(m_LblPump1, Gtk::PACK_EXPAND_PADDING);    
        m_HBox1.pack_start(m_EntryPump1, Gtk::PACK_EXPAND_PADDING);    
        m_VBox1.pack_start(m_HBox1, Gtk::PACK_EXPAND_PADDING);    
        m_HBox2.pack_start(m_LblPump2, Gtk::PACK_EXPAND_PADDING);    
        m_HBox2.pack_start(m_EntryPump2, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox2, Gtk::PACK_EXPAND_PADDING);  
        m_HBox3.pack_start(m_BtnSave, Gtk::PACK_EXPAND_PADDING);    
        m_HBox3.pack_start(m_BtnCancel, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox3, Gtk::PACK_EXPAND_PADDING);  
        
        add(m_VBox1);       
        
        //connect signals to handlers
        m_BtnSave.signal_clicked().connect(sigc::mem_fun(*this, &EditRecipeWindow::on_save_button_clicked));
	m_BtnCancel.signal_clicked().connect(sigc::mem_fun(*this, &EditRecipeWindow::on_cancel_button_clicked));
        
        show_all_children();  
}

EditRecipeWindow::~EditRecipeWindow()
{
    
}
//signal handlers
void EditRecipeWindow::on_save_button_clicked()
{
    
    
    cout << "Save" << std::endl;
     
    
}

void EditRecipeWindow::on_cancel_button_clicked()
{
    cout << "Cancel" << std::endl;
  
}
