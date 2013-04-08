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

void GameOfLife::fill_cell(int r, int c)
{
  if( !(r*CELL_DIMENSION > SCREEN_WIDTH || r < 0 ||
	c*CELL_DIMENSION > SCREEN_HEIGHT || c < 0) )
      boxRGBA( _screen,
	       r*CELL_DIMENSION, c*CELL_DIMENSION,
	       (r+1)*CELL_DIMENSION, (c+1)*CELL_DIMENSION,
	       BLACK_R, BLACK_G, BLACK_B, OPAQUE);
}

		     

int GameOfLife::n_live_neighbors(int r, int c)
{
  int count = 0;

  int l = this->c_left(r,c);
  int t = this->c_right(r,c);
  int u = this->c_up(r,c);
  int d = this->c_down(r,c);  
  
  count += _field[r][l] ? 1 : 0;
  count += _field[r][t] ? 1 : 0;
  count += _field[u][c] ? 1 : 0;
  count += _field[d][c] ? 1 : 0;
  count += _field[u][l] ? 1 : 0;
  count += _field[d][l] ? 1 : 0;
  count += _field[u][r] ? 1 : 0;
  count += _field[d][r] ? 1 : 0;

  return count;
}


int GameOfLife::c_left(int r, int c)
{
  if( c <= 0 )
    return FIELD_DIMENSION-1;
  return c-1;
}

int GameOfLife::c_right(int r, int c)
{
  if( c >= (FIELD_DIMENSION-1) )
    return 0;
  return c+1;
}

int GameOfLife::c_up(int r, int c)
{
  if( r <= 0 )
    return FIELD_DIMENSION-1;
  return r-1;
}

int GameOfLife::c_down(int r, int c)
{
  if( r >= (FIELD_DIMENSION-1) )
    return 0;
  return r+1;
}

