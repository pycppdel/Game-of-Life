#ifndef __GAME_OBJECTS__
#define __GAME_OBJECTS__

class Cell{

private:

int x, y;
int width;
SDL_Color color;
SDL_Renderer* renderer_pointer;
SDL_Rect blockrect;

public:

  Cell();
  Cell(int, int, int, SDL_Color&, SDL_Renderer*);

  void draw();
  void reset_renderer(SDL_Renderer*);

};

class Field{

public:
  Cell*** cells;
  bool** living;
  SDL_Renderer* r;
  int width, height, cellsize;
  SDL_Color cellcolor = {0xFF, 0xFF, 0xFF};


  Field();
  Field(int, int, int, SDL_Renderer*); //int for width and height
  Field(Field&);
  ~Field();

  Field& operator=(Field&);

  void transform(); //transforms field in one step
  void draw();
  void fill_randomly();


};

Cell::Cell(){

}

Cell::Cell(int x, int y, int width, SDL_Color& c, SDL_Renderer* r){

  this->x = x;
  this->y = y;
  this->width = width;
  color.r = c.r;
  color.g = c.g;
  color.b = c.b;
  renderer_pointer = r;

}

void Cell::draw(){

  blockrect.x = x;
  blockrect.y = y;
  blockrect.w = width;
  blockrect.h = width;
  SDL_SetRenderDrawColor(renderer_pointer, color.r, color.g, color.b, 0x0);
  SDL_RenderFillRect(renderer_pointer, &blockrect);


}

void Cell::reset_renderer(SDL_Renderer* r){
  renderer_pointer = r;
}

Field::Field(){

}

Field::Field(int w, int h, int cellw, SDL_Renderer* rend){

  r = rend;

  width = w;
  height = h;
  cellsize = cellw;

  //creating cells
  cells = new Cell**[width];
  for(int i=0;i<width;i++){
    cells[i] = new Cell*[height];
    for(int z= 0;z < height;z++){
      cells[i][z] = new Cell(z*cellsize, i*cellsize, cellsize, cellcolor, r);
    }
  }

  //creating bool field

  living = new bool*[width];
  for(int i=0;i<width;i++){
    living[i] = new bool[height];
    for(int z = 0; z < height; z++){
      living[i][z] = false;
    }
  }



}

Field& Field::operator=(Field& f){

  r =f.r;

  width = f.width;
  height = f.height;
  cellsize = f.cellsize;

  cells = new Cell**[width];
  for(int i=0;i<width;i++){
    cells[i] = new Cell*[height];
    for(int z= 0;z < height;z++){
      cells[i][z] = new Cell(z*cellsize, i*cellsize, cellsize, cellcolor, r);
    }
  }

  living = new bool*[width];
  for(int i=0;i<width;i++){
    living[i] = new bool[height];
    for(int z = 0; z < height; z++){
      living[i][z] = f.living[i][z];
    }
  }

  return (*this);
}

Field::Field(Field& f){

  r = f.r;

  width = f.width;
  height = f.height;
  cellsize = f.cellsize;

  cells = new Cell**[width];
  for(int i=0;i<width;i++){
    cells[i] = new Cell*[height];
    for(int z= 0;z < height;z++){
      cells[i][z] = new Cell(z*cellsize, i*cellsize, cellsize, cellcolor, r);
    }
  }

  living = new bool*[width];
  for(int i=0;i<width;i++){
    living[i] = new bool[height];
    for(int z = 0; z < height; z++){
      living[i][z] = f.living[i][z];
    }
  }


}

Field::~Field(){

  for(int i = 0; i < width;i++){

    for(int z = 0;z < height;z++){

      delete cells[i][z];
    }

    delete [] cells[i];
  }

  delete [] cells;

  for(int i = 0; i < width;i++){

  delete [] living[i];
  }

  delete [] living;

}

void Field::transform(){

  bool** im_copy;
  im_copy = new bool*[width];
  for(int i=0;i<width;i++){
    im_copy[i] = new bool[height];
    for(int z = 0; z< height;z++){
      im_copy[i][z] = living[i][z];
    }
  }

  //transforming
  int counter = 0;

  for(int i=0; i< width;i++){
    for(int z = 0; z < height; z++){

      counter = 0;
      for(int w_c = -1; w_c <= 1; w_c++){
        for(int h_c = -1; h_c <= 1; h_c++){
          if(i+w_c < 0 || i+w_c >= width || z+h_c < 0 || z+h_c >= height || (w_c == 0 && h_c == 0)){
            continue;
          }
          else{
            if(living[i+w_c][z+h_c]){
              counter++;
            }
          }
        }
      }

      if (counter < 2 || counter > 3){
        im_copy[i][z] = false;
      }
      else if(counter == 3){
        im_copy[i][z] = true;
      }

    }
  }


  //copying

  for(int i=0;i<width;i++){
    for(int z = 0; z< height;z++){
      living[i][z] = im_copy[i][z];
    }
  }


  //cleaning up

  for(int i=0; i< width; i++){
    delete [] im_copy[i];
  }
  delete [] im_copy;
}

void Field::draw(){

  for(int i = 0; i< width; i++){
    for(int z = 0; z < height; z++){
      if (living[i][z]){
        cells[i][z]->draw();
      }
    }
  }
}

void Field::fill_randomly(){

  for(int i=0;i<this->width;i++){
  for(int z = 0; z < this->height; z++){
    living[i][z] = ((rand()%2) == 1);
  }
}

}


#endif
