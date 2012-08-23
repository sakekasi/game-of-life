#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "game-of-life.hh"

class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    Gtk::Frame m_frame;
    GameOfLife game;

};

#endif
    
    
        
