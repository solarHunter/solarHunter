#ifndef H_SDL_HEADERS
#define H_SDL_HEADERS

// #if defined(_MSC_VER)
// #include <SDL.h>
// #include <SDL_ttf.h>
// #include <SDL_image.h>
// #elif defined(__APPLE__)
// #include <SDL.h>
// #include <SDL_ttf.h>
// #include <SDL_image.h>
// #else
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_image.h>
// #endif

  #ifdef __linux
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
  #elif __APPLE__
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
  #endif

#endif
