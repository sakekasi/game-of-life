#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toggletoolbutton.h>
#include "game-of-life.hh"

class MainWindow : public Gtk::Window
{
public:
        MainWindow();
        virtual ~MainWindow();
        
protected:
        Gtk::Box vbox;
        GameOfLife game;

        Gtk::Toolbar toolbar;
        Gtk::ToggleToolButton run,grid_on;
};

#endif        
