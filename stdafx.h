#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <cstddef>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include <utility>
#include <ctime>
#include <iostream>

//first to include: standarddef for standard definitions
#ifndef __STANDARDDEF__
#include "standarddef.hpp"
#endif

#ifndef __TIMER__
#include "timer.hpp"
#endif

#ifndef __DECRYPTOR__
#include "decryptor.hpp"
#endif

#ifndef __GAME_OBJECTS__
#include "game_objects.hpp"
#endif

#ifdef __linux__
#include <png.h>
#include <zlib.h>
#endif

#ifdef _WIN32
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#undef main
#endif
