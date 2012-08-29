#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <gtkmm/drawingarea.h>

#define TOP_YCOORD 0
#define LEFT_XCOORD 0
#define GRID_ROWS 1000
#define GRID_COLS 1000
#define REFRESH_TIME_MILLIS 100
#define PAUSE true
#define PLAY false

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

        void play_pause();

        bool grid_on();
        bool set_grid_on(bool);
        void toggle_grid();

        void reset();
        
        
protected:
        //drawing
        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>&);

        //specific drawing parts
        bool draw_grid(const Cairo::RefPtr<Cairo::Context>&);
        bool fill_grid(const Cairo::RefPtr<Cairo::Context>&);
        bool fill_square(const Cairo::RefPtr<Cairo::Context>&, int, int);

        //gui input (signal handlers)
        bool on_timeout();
        bool on_click(GdkEventButton *);
        bool on_mouse_move(GdkEventMotion *);

        //game engine
        bool tick();
        void create_updated_grid();
        bool cells_get(int,int);
        void next_cells_set(int,int,bool);
        bool **next_cells_init();
        
        int columns;
        int rows;
        
        int width;
        int height;
        
        int col_width;
        int row_height;
        
        int l_width;

        bool paused;
        bool grid;
        
        bool** cells;
        bool** next_cells;
        
};


#endif
