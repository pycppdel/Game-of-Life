#ifndef __DECRYPTOR__
#define __DECRYPTOR__


class Crypt{

private:

  int argc = -1;
  char** argv = NULL;

public:

  Crypt();
  Crypt(int, char**);
  ~Crypt();

  int get_width();
  int get_height();
  int get_cellsize();
  int get_fps();
  bool get_random();

};



Crypt::Crypt(){

}

Crypt::Crypt(int argc, char** argv){

  this->argc = argc;
  this->argv = argv;

}

Crypt::~Crypt(){

}

int Crypt::get_width(){

  if (argv == NULL){

    return -1;
  }

  int back = 0;
  std::stringstream stream;

  for(int i=0;i<argc;i++){

    if (strncmp("-w", argv[i], strlen(argv[i])) == 0){

      //found
      stream << argv[i+1];
      stream >> back;
      return back;

    }


  }

  return STANDARD_WIDTH;
}


int Crypt::get_height(){

  if (argv == NULL){

    return -1;
  }

  int back = 0;
  std::stringstream stream;

  for(int i=0;i<argc;i++){

    if (strncmp("-h", argv[i], strlen(argv[i])) == 0){

      //found
      stream << argv[i+1];
      stream >> back;
      return back;

    }


  }

  return STANDARD_HEIGHT;
}

int Crypt::get_cellsize(){

  if (argv == NULL){

    return -1;
  }
  int back;
  std::stringstream stream;
  for(int i=0;i<argc;i++){

    if (strncmp("-cs", argv[i], strlen(argv[i])) == 0){

      //found
      stream << argv[i+1];
      stream >> back;
      return back;

    }


  }

  return CELLSIZE;

}

int Crypt::get_fps(){

  if (argv == NULL){

    return -1;
  }
  int back;
  std::stringstream stream;
  for(int i=0;i<argc;i++){

    if (strncmp("-fps", argv[i], strlen(argv[i])) == 0){

      //found
      stream << argv[i+1];
      stream >> back;
      return back;

    }


  }

  return FPS;

}

bool Crypt::get_random(){

  if (argv == NULL){

    return false;
  }
  int back;
  std::stringstream stream;
  for(int i=0;i<argc;i++){

    if (strncmp("--random", argv[i], strlen(argv[i])) == 0){

    return true;
    }


  }

  return false;

}

#endif
