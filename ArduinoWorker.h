/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArduinoWorker.h
 * Author: root
 *
 * Created on June 27, 2017, 6:24 PM
 */

#ifndef ArduinoWorker_H
#define ArduinoWorker_H


#include <gtkmm.h>
#include <thread>
#include <mutex>
#include <string>

class FrmMain;

class ArduinoWorker
{
public:
  ArduinoWorker();

  // Thread function.
  void do_work(FrmMain* caller);
  void set_data(std::string* pump_command);
  void stop_work();
  bool has_stopped() const;
  
private:
  // Synchronizes access to member data.
  mutable std::mutex m_Mutex;

  // Data used by both GUI thread and worker thread.
  bool m_shall_stop;
  bool m_has_stopped;
  std::string m_pump_command; 
};


#endif /* ArduinoWorker_H */

