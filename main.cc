#include "game-of-life.hh"
#include "constants.hh"

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <string>
#include <iostream>
using namespace std;

int main( int argc, char* argv[] )
{
  
  SDL_Surface* screen = NULL;
  
  if( SDL_Init( SDL_INIT_EVERYTHING == -1 ) )
    return 1;

  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
			     SDL_SWSURFACE);

  SDL_WM_SetCaption( WINDOW_TITLE.c_str() , NULL);

  GameOfLife game(screen);

  SDL_Event event;
  bool gameRunning = true;
  bool left_clicked = false, right_clicked = false;
  bool iterating = false;

  while(gameRunning)
    {
      while( SDL_PollEvent(&event) )
	{
	  if( event.type == SDL_QUIT )
	    gameRunning = false;
	  else if( event.type == SDL_MOUSEBUTTONDOWN )
	    {
	      int x = event.button.x;
	      int y = event.button.y;
	      
	      if( event.button.button == SDL_BUTTON_LEFT )
		{
		  left_clicked = true;
		  game.set_true(x,y);
		}
	      else if( event.button.button == SDL_BUTTON_RIGHT )
		{
		  right_clicked = true;
		  game.set_false(x,y);
		}
	    }
	  else if( event.type == SDL_MOUSEBUTTONUP )
	    {
	      int x = event.button.x;
	      int y = event.button.y;

	      if( event.button.button == SDL_BUTTON_LEFT )
		left_clicked = false;
	      if( event.button.button == SDL_BUTTON_RIGHT )
		right_clicked = false;
	    }
	  else if( event.type == SDL_MOUSEMOTION )
	    {
	      int x = event.motion.x;
	      int y = event.motion.y;

	      if( left_clicked )
		game.set_true(x,y);
	      else if( right_clicked )
		{
		  cout << "right clicked" << endl;
		  game.set_false(x,y);
		}
	    }
	  else if( event.type == SDL_KEYDOWN )
	    {
	      switch( event.key.keysym.sym )
		{
		case SDLK_SPACE:
		  iterating = !(iterating);
		}
	    }
	}
    
      game.draw();

      SDL_Flip(screen);
      SDL_Delay(1);
      if(iterating)
	game.iterate();
    }

  SDL_FreeSurface(screen);
  SDL_Quit();

  return 0;
}
	

