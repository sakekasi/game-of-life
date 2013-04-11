#include "game-of-life.hh"
#include "constants.hh"

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <algorithm>
using namespace std;

//HELPER FUNCTIONS
////////////////////////////////////////////////////////////////////
void init_field_array(bool*& b)
{
  b = new bool[FIELD_DIMENSION];
}

void del_field_array(bool *b)
{
  delete [] b;
}


//PUBLIC INTERFACE
/////////////////////////////////////////////////////////////////////
GameOfLife::GameOfLife(SDL_Surface *s)
  :_screen(s)
{
  _field = new bool*[FIELD_DIMENSION];
  for_each(_field, _field+FIELD_DIMENSION, init_field_array);

  for(int i=0; i<FIELD_DIMENSION; i++)
    for(int j=0; j<FIELD_DIMENSION; j++)
      _field[i][j] = false;
}

GameOfLife::~GameOfLife()
{
  for_each(_field, _field+FIELD_DIMENSION, del_field_array);
  delete[] _field;
}

void GameOfLife::draw()
{
  this->draw_background();
  this->draw_lines();
  this->fill_cells();
}

void GameOfLife::iterate()
{
  bool **new_field = new bool*[FIELD_DIMENSION];
  for_each(new_field, new_field+FIELD_DIMENSION, init_field_array);
  for(int i=0; i<FIELD_DIMENSION; i++)
    for(int j=0; j<FIELD_DIMENSION; j++)
      new_field[i][j] = false;

  
  for( int i=0; i<FIELD_DIMENSION; i++ )
    for( int j=0; j<FIELD_DIMENSION; j++ )
      {
	int live_neighbors = this->n_live_neighbors(i,j);
	if( _field[i][j] )
	  {
	  if( live_neighbors < 2)
	    new_field[i][j] = false;
	  else if( live_neighbors > 3)
	    new_field[i][j] = false;
	  else
	    new_field[i][j] = true;
	  }
	else
	  if( live_neighbors == 3)
	    new_field[i][j] = true;
	  else
	    new_field[i][j] = false;
      }

    for_each(_field, _field+FIELD_DIMENSION, del_field_array);
    delete[] _field;

    _field = new_field;
}

void GameOfLife::reset()
{
  for_each(_field, _field+FIELD_DIMENSION, del_field_array);
  delete[] _field;
  
  _field = new bool*[FIELD_DIMENSION];
  for_each(_field, _field+FIELD_DIMENSION, init_field_array);

  for(int i=0; i<FIELD_DIMENSION; i++)
    for(int j=0; j<FIELD_DIMENSION; j++)
      _field[i][j] = false;

}



void GameOfLife::set_true(int x, int y)
{
  int r = x/CELL_DIMENSION;
  int c = y/CELL_DIMENSION;

  _field[r][c] = true;
}

void GameOfLife::set_false(int x, int y)
{
  int r = x/CELL_DIMENSION;
  int c = y/CELL_DIMENSION;

  _field[r][c] = false;
}

  


//PRIVATE FUNCTIONS
/////////////////////////////////////////////////////////////////////
void GameOfLife::draw_background()
{
  boxRGBA( _screen,
	   LEFT, TOP,
	   SCREEN_WIDTH, SCREEN_HEIGHT,
	   WHITE_R, WHITE_G, WHITE_B, OPAQUE );
}


void GameOfLife::draw_lines()
{
  int width = _screen->w;
  int height = _screen->h;
  int n_lines;

  //horizontal lines
  n_lines = width / CELL_DIMENSION;  
  for( int i=1; i<=n_lines; i++)
    {
      thickLineRGBA( _screen, //destination surface
		     CELL_DIMENSION*i, TOP, //starting point
		     CELL_DIMENSION*i, height, //ending point
		     LINE_WIDTH, //thickness
		     BLACK_R, BLACK_G, BLACK_B, OPAQUE); //color
    }

  //vertical lines
  n_lines = height / CELL_DIMENSION;
  for( int i=1; i<= n_lines; i++)
    {
      thickLineRGBA( _screen,
		     LEFT, CELL_DIMENSION*i,
		     width, CELL_DIMENSION*i,
		     LINE_WIDTH,
		     BLACK_R, BLACK_G, BLACK_B, OPAQUE);
    }
}

void GameOfLife::fill_cells()
{
  for( int i=0; i < FIELD_DIMENSION; i++ )
    for( int j=0; j < FIELD_DIMENSION; j++ )
      if( _field[i][j] )
	this->fill_cell(i,j);
}

void GameOfLife::fill_cell(int x, int y)
{
  if( !(x*CELL_DIMENSION > SCREEN_WIDTH || x < 0 ||
	y*CELL_DIMENSION > SCREEN_HEIGHT || y < 0) )
      boxRGBA( _screen,
	       x*CELL_DIMENSION, y*CELL_DIMENSION,
	       (x+1)*CELL_DIMENSION, (y+1)*CELL_DIMENSION,
	       BLACK_R, BLACK_G, BLACK_B, OPAQUE);
}

		     

int GameOfLife::n_live_neighbors(int x, int y)
{
  int count = 0;

  int l = this->c_left(x,y);
  int r = this->c_right(x,y);
  int u = this->c_up(x,y);
  int d = this->c_down(x,y);  
  
  count += _field[l][y] ? 1 : 0;
  count += _field[r][y] ? 1 : 0;
  count += _field[x][u] ? 1 : 0;
  count += _field[x][d] ? 1 : 0;
  count += _field[l][u] ? 1 : 0;
  count += _field[l][d] ? 1 : 0;
  count += _field[r][u] ? 1 : 0;
  count += _field[r][d] ? 1 : 0;

  return count;
}


int GameOfLife::c_left(int x, int y)
{
  if( x <= 0 )
    return FIELD_DIMENSION-1;
  return x-1;
}

int GameOfLife::c_right(int x, int y)
{
  if( x >= (FIELD_DIMENSION-1) )
    return 0;
  return x+1;
}

int GameOfLife::c_up(int x, int y)
{
  if( y <= 0 )
    return FIELD_DIMENSION-1;
  return y-1;
}

int GameOfLife::c_down(int x, int y)
{
  if( y >= (FIELD_DIMENSION-1) )
    return 0;
  return y+1;
}

