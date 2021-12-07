/*
*
*  @Author Paul Walcher
*
*  @Date 3.12.2021
*
*  Implementation of Conways Game of life
*
*/

#include "stdafx.h"
//definitions

//variables


SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event e;

void init();
void draw();
void end();

int get_cell_row_count();
int get_cell_column_count();

void call_global_transform();

//for width: -w [NUMBER]
int width = STANDARD_WIDTH;
//for height: -h [NUMBER]
int height = STANDARD_HEIGHT;
//color: set color via -c [R]_[G]_[B]; example: -c 255_0_0
SDL_Color background_color = {128, 128, 128};
//cellsize for cells
int cellsize = CELLSIZE;
//fps for fps, set by -fps [NUMBER]
int fps = FPS;

Field global_field;


SDL_Color white = {0xFF, 0xFF, 0xFF};



int main(int argc, char** argv){

  //init process
  init();
  srand(time(NULL));


  Crypt crypt(argc, argv);
  ::width = crypt.get_width();
  ::height = crypt.get_height();
  ::cellsize = crypt.get_cellsize();
  ::fps = crypt.get_fps();
  //now variables should be declared or initialized
  Field cop(get_cell_row_count(), get_cell_column_count(), cellsize, renderer);
  global_field = cop;
  global_field.fill_randomly();

  Timer tim(static_cast<int>(1000/fps));
  tim.set_f(call_global_transform);



  bool quit = false;

  while (!quit){

    SDL_PollEvent(&e);

    switch(e.type){

      case SDL_QUIT:
                    quit = true;
                    break;

    }
    tim.tick();
    draw();

  }

  end();

  exit(0);
}


void init(){

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  window = SDL_CreateWindow("Game Of Life", 100, 100, width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}


void draw(){

  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 0x0);
  global_field.draw();
  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 0x0);
  SDL_RenderPresent(renderer);

}

void end(){

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int get_cell_row_count(){

  return static_cast<int>(width/cellsize);

}

int get_cell_column_count(){

  return static_cast<int>(height/cellsize);
}

void call_global_transform(){
  global_field.transform();
}
