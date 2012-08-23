#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <gtkmm/drawingarea.h>

#define TOP_YCOORD 0
#define LEFT_XCOORD 0

class GameOfLife : public Gtk::DrawingArea
{
public:
        GameOfLife();
        virtual ~GameOfLife();
        
        int get_cols();
        int get_rows();
        
        int get_width();
        int get_height();
        
        int get_col_width();
        int get_row_height();
        
protected:
        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
        bool draw_grid(const Cairo::RefPtr<Cairo::Context>& cr);
        bool on_timeout();
        
        int columns;
        int rows;
        
        int width;
        int height;
        
        int col_width;
        int row_height;
        
        int l_width;
        
        bool** cells;
};

#endif
