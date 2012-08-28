/*
 *game-of-life.cc
 *
 *An implementation of the Gtk::DrawingArea subclass outlined in
 *game-of-life.hh
 *
 *-------------------------------------------------------------------------
 *there are three layers here:
 *
 *the abstract layer (the user's layer) whose code is as simple and
 *perfect as possible.
 *
 *the magic layer, which isthe layer that sits in between and handles edge
 *cases such as indices of -1 etc. etc.
 *
 *the binary layer where the actual data stored in a 2d array.
 *
 *-------------------------------------------------------------------------
 *these three layers will be used to provide user I/O as well as a
 *method to handle the data such that when executing a generation of
 *the game of life, each index in the data is only accessed once.
 *
 *Author: Saketh Kasibatla
 */

#include <iostream>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include "game-of-life.hh"

/*
 *constructors / destructors
 */

GameOfLife::GameOfLife()
        : l_width(1), col_width(15), row_height(15)
{
        //initialize binary layer (grid)
        this->cells = (bool **) calloc( GRID_ROWS  , sizeof(bool *));
        
        int i,j;
        for(i=0;i < GRID_ROWS;i++){
                this->cells[i] = (bool *) calloc( GRID_COLS , sizeof(bool));
                for(j=0;j < GRID_COLS ;j++){
                        this->cells[i][j] = false;
                }
        }

        //set up signals
        
        Glib::signal_timeout().connect(sigc::mem_fun(*this, &GameOfLife::tick), REFRESH_TIME_MILLIS );
#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
        //Connect the signal handler if it isn't already a virtual method override:
        signal_draw().connect(sigc::mem_fun(*this, &GameOfLife::on_draw), false);
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED

        this->signal_button_press_event().connect( sigc::mem_fun(*this, &GameOfLife::on_click), false);
        this->signal_motion_notify_event().connect(sigc::mem_fun(*this, &GameOfLife::on_mouse_move), false);
        this->set_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);
        

}

GameOfLife::~GameOfLife()
{
}


/*
 *accessors
 */

int GameOfLife::get_cols()
{
        return this->columns;
}

int GameOfLife::get_rows()
{
        return this->rows;
}


int GameOfLife::get_width()
{
        return this->width;
}

int GameOfLife::get_height()
{
        return this->height;
}


int GameOfLife::get_col_width()
{
        return this->col_width;
}

int GameOfLife::get_row_height()
{
        return this->row_height;
}

/*
 *painting functions
 */

bool GameOfLife::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
        this->width = this->get_allocation().get_width();
        this->height = this->get_allocation().get_height();
        
        this->columns = this->width / this->col_width;
        this->rows = this->height / this->row_height;
        
        
        cr->set_line_width(l_width);
        cr->set_source_rgb(1.0 , 1.0 , 1.0);
        cr->paint();
        cr->save();
        
        this->draw_grid(cr);
        this->fill_grid(cr);
        
        return true;
}

bool GameOfLife::draw_grid(const Cairo::RefPtr<Cairo::Context>& cr)
{
        cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
        cr->set_source_rgb(0.0 , 0.0 , 0.0);    
        
        int i;
        for( i=0 ; i < this->get_width(); i += this->get_col_width() ){
                cr->save();
                
                cr->move_to(i, TOP_YCOORD);
                cr->line_to(i, this->get_height());
                
                cr->stroke();
                cr->restore();
        }
        
        for( i=0 ; i < this->get_height() ; i += this->get_row_height() ){
                cr->save();
                
                cr->move_to(LEFT_XCOORD, i);
                cr->line_to(this->get_width() , i);
                
                cr->stroke();
                cr->restore();
        }
        
        return true;
}

bool GameOfLife::fill_grid(const Cairo::RefPtr<Cairo::Context>& cr)
{
        int i,j;

        for(i=0;i<this->get_rows();i++){
                for(j=0;j<this->get_cols();j++){
                        if(this->cells[i][j]){
                                this->fill_square(cr, i,j);
                        }
                }
        }

        return true;
}

bool GameOfLife::fill_square(const Cairo::RefPtr<Cairo::Context>& cr, int c, int r)
{
        int x=this->get_col_width()*c , y=this->get_row_height()*r;

        cr->set_source_rgb(0.0, 0.0, 0.0);
        
        cr->save();
        cr->rectangle(x,y,this->get_col_width(), this->get_row_height());
        cr->fill();
        cr->restore();
        
        return true;
}

bool GameOfLife::on_click(GdkEventButton *event)
{

        int x = ( (int) event->x ) / this->get_col_width();
        int y = ( (int) event->y ) / this->get_row_height();

        this->cells[x][y] = !this->cells[x][y];
        
        
        return this->on_timeout();
}

bool GameOfLife::on_mouse_move(GdkEventMotion *event)
{
        static int last_x=-1, last_y=-1;
        int x, y;
        
        x=( (int) event->x ) / this->get_col_width();
        y=( (int) event->y ) / this->get_row_height();

        if( event->state & GDK_BUTTON1_MASK ){
                this->cells[x][y] = true;
        } else if ( event->state & GDK_BUTTON3_MASK ){
                this->cells[x][y] = false;
        }
        

        return this->on_timeout();
}

bool GameOfLife::on_timeout()
{
        Glib::RefPtr<Gdk::Window> win = get_window();
        
        if (win)
        {
                Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                                 get_allocation().get_height());
                win->invalidate_rect(r, false);
        }
        return true;
}

bool GameOfLife::tick()
{
        return this->on_timeout();
}
