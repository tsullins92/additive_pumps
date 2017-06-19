/*
 * FrmMain.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: tim
 */

#include "FrmMain.h"
#include "AsyncSerial.h"
#include <iostream>
#include <termios.h>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <string>
#include <sigc++/sigc++.h>

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
        builder->get_widget("lblMass",lblMass);
        
	btnOk->signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_ok_button_clicked));
	btnCancel->signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_cancel_button_clicked));
        start_serial_read("/dev/ttyUSB0",4800);
        
}

FrmMain::type_scale_read Frm::main scale_read(){
    if (prevScaleReading != scaleReading){
        
    }
}

void FrmMain::on_ok_button_clicked(){
	labelSentStatus->set_text("Sent");
}

void FrmMain::on_cancel_button_clicked(){
	labelSentStatus->set_text("");
}

void FrmMain::on_scale_read(){
        lblMass->set_text(scaleReading);
}

void FrmMain::received(const char *data, unsigned int len)
{   
    string scaleReading;
    ostringstream os;
    vector<char> v(data,data+len);
    for(unsigned int i=0;i<v.size();i++)
    {
        if((v[i]=='\n'))
        {
            scaleReading = os.str();
            
        } else {
            if(v[i]<32 || v[i]>=0x7f) os.put(' ');//Remove non-ascii char
            else os.put(v[i]);
        }
    }
    os.flush();//Flush screen buffer
}

static void FrmMain::start_serial_read(string dev,unsigned int baud)
{   
    termios stored_settings;
    tcgetattr(0, &stored_settings);
    termios new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ISIG); // don't automatically handle control-C
    new_settings.c_lflag &= ~(ECHO); // no echo
    tcsetattr(0, TCSANOW, &new_settings);
//newfile
    cout<<"\e[2J\e[1;1H"; //Clear screen and put cursor to 1;1

    try {
        CallbackAsyncSerial serial(dev,baud);
        serial.setCallback(received);
        for(;;)
        {
            if(serial.errorStatus() || serial.isOpen()==false)
            {
                cerr<<"Error: serial port unexpectedly closed"<<endl;
                break;
            }
            //char c;
            //cin.get(c); //blocking wait for standard input
            //if(c==3) //if Ctrl-C
           // {
           //     cin.get(c);
           //     switch(c)
           //     {
           //         case 3:
           //             //serial.write(&c,1);//Ctrl-C + Ctrl-C, send Ctrl-C
           //         break;
           //         case 'x': //fall-through
           //         case 'X':
           //             goto quit;//Ctrl-C + x, quit
           //         default:
                        //serial.write(&c,1);//Ctrl-C + any other char, ignore
           //     }
           // } else serial.write(&c,1);
        }
        quit:
        serial.close();
    } catch (std::exception& e) {
        cerr<<"Exception: "<<e.what()<<endl;
    }

    tcsetattr(0, TCSANOW, &stored_settings);
}

