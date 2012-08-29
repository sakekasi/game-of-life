/*
 *main-window.cc
 *
 *the main window for the program
 *
 *Author: Saketh Kasibatla
 */

#include <iostream>
#include <gtkmm/stock.h>
#include "main-window.hh"

MainWindow::MainWindow()
        :Gtk::Window(), game(), vbox(Gtk::ORIENTATION_VERTICAL), run("Run"),
         grid_on("Hide Grid"), reset("Reset"), toolbar()
{
        this->set_title("Conway's Game of Life");
        //get rid of hard coded stuff
        set_default_size(400,400);

        this->run.signal_toggled().connect(sigc::mem_fun(this->game, &GameOfLife::play_pause));
        this->grid_on.signal_toggled().connect(sigc::mem_fun(this->game, &GameOfLife::toggle_grid));
        this->reset.signal_clicked().connect(sigc::mem_fun(this->game, &GameOfLife::reset));

        this->toolbar.append(this->run);
        this->toolbar.append(this->grid_on);
        this->toolbar.append(this->reset);

        this->vbox.pack_start(this->toolbar, Gtk::PACK_SHRINK);
        this->vbox.pack_start(this->game);
        
        
        this->add(vbox);
        this->show_all_children();
}

MainWindow::~MainWindow()
{
}    
