#ifndef H_HEADERS
#define H_HEADERS

#include <iostream>
#include <stdlib.h>

// Core
#ifdef __linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#include "constants.h"

#endif
