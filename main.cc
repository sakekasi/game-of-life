/*
 *main.cc
 *
 *Main file for conway's game of life
 *
 *Author: Saketh Kasibatla
 */

#include <gtkmm/application.h>
#include "game-of-life.hh"
#include "main-window.hh"

int main(int argc, char **argv)
{
//    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    Gtk::Main main(argc, argv);
        
    MainWindow win;
    win.set_title("Game of Life");

    main.run(win);
    return 0;
}
