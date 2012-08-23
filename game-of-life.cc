/*
 *game-of-life.cc
 *
 *An implementation of the Gtk::DrawingArea subclass outlined in game-of-life.hh
 *
 *Author: Saketh Kasibatla
 */

#include <cairomm/context.h>
#include <glibmm/main.h>
#include "game-of-life.hh"

/*
 *constructors / destructors
 */

GameOfLife::GameOfLife()
    : l_width(1)
{
    this->col_width = 15;
    this->row_height = 15;

    this->cells = (bool **) calloc( this->get_rows() , sizeof(bool *));

    int i,j;
    for(i=0;i < this->get_rows();i++){
        this->cells[i] = (bool *) calloc( this->get_cols() , sizeof(bool));
        for(j=0;j < this->get_cols() ;j++){
            this->cells[i][j] = false;
        }
    }

    
    
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &GameOfLife::on_timeout),
                                    100 );
    #ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
    //Connect the signal handler if it isn't already a virtual method override:
    signal_draw().connect(sigc::mem_fun(*this, &GameOfLife::on_draw), false);
    #endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
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
    cr->set_source_rgba(0.0 , 0.0 , 0.0 , 1.0);
    cr->paint();
    cr->save();

    this->draw_grid(cr);

    return true;
}

bool GameOfLife::draw_grid(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
    cr->set_source_rgba(1.0 , 1.0 , 1.0 , 1.0);    
    
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
