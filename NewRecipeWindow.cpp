/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "NewRecipeWindow.h"
#include <gtkmm.h>
#include <iostream>

using namespace std;
using namespace Gtk;


NewRecipeWindow::NewRecipeWindow()
      : //Initialize gui elements
        m_BtnSave("Save"),          //m_BtnSave displays "Save"   
        m_BtnCancel("Cancel"),        //m_BtnCancel displays "Cancel"
        m_LblPump1("Pump 1: "),
        m_LblPump2("Pump 2: "),
        m_LblPump3("Pump 3: "),
        m_LblPump4("Pump 4: "),
        m_LblPump5("Pump 5: "),
        m_LblPump6("Pump 6: "),
        m_LblPump7("Pump 7: "),
        m_LblPump8("Pump 8: "),
        m_LblPump9("Pump 9: "),
        m_LblPump10("Pump 10: "),
        m_VBox1(Gtk::ORIENTATION_VERTICAL),       
        m_HBox1(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox2(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox3(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox4(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox5(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox6(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox7(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox8(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox9(Gtk::ORIENTATION_HORIZONTAL),
        m_HBox10(Gtk::ORIENTATION_HORIZONTAL)
{       
        //more initializing and packing elements into window
        set_title("Edit Recipes");
        //set_size_request(350,300);
        set_border_width(0);
        m_EntryPump1.set_text("mL/L");
        m_EntryPump2.set_text("mL/L");
        m_EntryPump3.set_text("mL/L");
        m_EntryPump4.set_text("mL/L");
        m_EntryPump5.set_text("mL/L");
        m_EntryPump6.set_text("mL/L");
        m_EntryPump7.set_text("mL/L");
        m_EntryPump8.set_text("mL/L");
        m_EntryPump9.set_text("mL/L");
        m_EntryPump10.set_text("mL/L");
        m_HBox1.pack_start(m_LblPump1, Gtk::PACK_EXPAND_PADDING);    
        m_HBox1.pack_start(m_EntryPump1, Gtk::PACK_EXPAND_PADDING);    
        m_VBox1.pack_start(m_HBox1, Gtk::PACK_EXPAND_PADDING);    
        m_HBox2.pack_start(m_LblPump2, Gtk::PACK_EXPAND_PADDING);    
        m_HBox2.pack_start(m_EntryPump2, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox2, Gtk::PACK_EXPAND_PADDING);  
        m_HBox3.pack_start(m_LblPump3, Gtk::PACK_EXPAND_PADDING);    
        m_HBox3.pack_start(m_EntryPump3, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox3, Gtk::PACK_EXPAND_PADDING);  
        m_HBox4.pack_start(m_LblPump4, Gtk::PACK_EXPAND_PADDING);    
        m_HBox4.pack_start(m_EntryPump4, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox4, Gtk::PACK_EXPAND_PADDING);  
        m_HBox5.pack_start(m_LblPump5, Gtk::PACK_EXPAND_PADDING);    
        m_HBox5.pack_start(m_EntryPump5, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox5, Gtk::PACK_EXPAND_PADDING);  
        m_HBox6.pack_start(m_LblPump6, Gtk::PACK_EXPAND_PADDING);    
        m_HBox6.pack_start(m_EntryPump6, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox6, Gtk::PACK_EXPAND_PADDING);  
        m_HBox7.pack_start(m_LblPump7, Gtk::PACK_EXPAND_PADDING);    
        m_HBox7.pack_start(m_EntryPump7, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox7, Gtk::PACK_EXPAND_PADDING);  
        m_HBox8.pack_start(m_LblPump8, Gtk::PACK_EXPAND_PADDING);    
        m_HBox8.pack_start(m_EntryPump8, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox8, Gtk::PACK_EXPAND_PADDING);  
        m_HBox9.pack_start(m_LblPump9, Gtk::PACK_EXPAND_PADDING);    
        m_HBox9.pack_start(m_EntryPump9, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox9, Gtk::PACK_EXPAND_PADDING);  
        m_HBox10.pack_start(m_LblPump10, Gtk::PACK_EXPAND_PADDING);    
        m_HBox10.pack_start(m_EntryPump10, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox10, Gtk::PACK_EXPAND_PADDING);         
        m_HBox11.pack_start(m_BtnSave, Gtk::PACK_EXPAND_PADDING);    
        m_HBox11.pack_start(m_BtnCancel, Gtk::PACK_EXPAND_PADDING);  
        m_VBox1.pack_start(m_HBox11, Gtk::PACK_EXPAND_PADDING);  
        
        add(m_VBox1);       
        
        //connect signals to handlers
        m_BtnSave.signal_clicked().connect(sigc::mem_fun(*this, &NewRecipeWindow::on_save_button_clicked));
	m_BtnCancel.signal_clicked().connect(sigc::mem_fun(*this, &NewRecipeWindow::on_cancel_button_clicked));
        
        show_all_children();  
}

NewRecipeWindow::~NewRecipeWindow()
{
    
}
//signal handlers
void NewRecipeWindow::on_save_button_clicked()
{
    
    
    cout << "Save" << std::endl;
     
    
}

void NewRecipeWindow::on_cancel_button_clicked()
{
    cout << "Cancel" << std::endl;
  
}
