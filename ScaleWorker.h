/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ScaleWorker.h
 * Author: root
 *
 * Created on June 27, 2017, 6:24 PM
 */

#ifndef SCALEWORKER_H
#define SCALEWORKER_H


#include <gtkmm.h>
#include <thread>
#include <mutex>
#include<string>

class FrmMain;

class ScaleWorker
{
public:
  ScaleWorker();

  // Thread function.
  void do_work(FrmMain* caller);

  void get_data(Glib::ustring* fraction_done) const;
  void stop_work();
  bool has_stopped() const;
  void control_ard();
  void control_active_pumps(std::string& reading,std::string target);
  
private:
  // Synchronizes access to member data.
  mutable std::mutex m_Mutex;

  // Data used by both GUI thread and worker thread.
  bool m_shall_stop;
  bool m_has_stopped;
  double m_fraction_done;
  std::string m_scale_reading;
};


#endif /* SCALEWORKER_H */

