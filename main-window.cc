/*
 *main-window.cc
 *
 *the main window for the program
 *
 *Author: Saketh Kasibatla
 */

#include "main-window.hh"

MainWindow::MainWindow()
    :Gtk::Window()
{
    this->add(m_frame);
    this->m_frame.set_label("Game of Life");
    this->m_frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    this->m_frame.add(this->game);

    this->show_all_children();
}

MainWindow::~MainWindow()
{
}


    
