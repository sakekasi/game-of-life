#ifndef GAME_OF_LIFE_HH
#define GAME_OF_LIFE_HH
#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

const Sint16 CELL_DIMENSION = 10; //pixels
const Uint8 LINE_WIDTH = 1; //pixels

const int FIELD_DIMENSION = 1000; //cells

const int TOP = 0;
const int LEFT = 0;

const Uint8 BLACK_R = 0;
const Uint8 BLACK_G = 0;
const Uint8 BLACK_B = 0;

const Uint8 WHITE_R = 255;
const Uint8 WHITE_G = 255;
const Uint8 WHITE_B = 255;

const Uint8 OPAQUE = 255;


class GameOfLife 
{
public:
  GameOfLife(SDL_Surface*);
  ~GameOfLife();

  void draw();
  void iterate();

  void set_true(int, int);
  void set_false(int, int);

private:

  SDL_Surface *_screen;
  bool **_field;

  void draw_background();
  void draw_lines();
  void fill_cells();
  void fill_cell(int, int);

  int n_live_neighbors(int, int);
  
  int c_left(int, int);
  int c_right(int, int);
  int c_up(int, int);
  int c_down(int, int);
};

#endif
