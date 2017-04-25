#ifndef H_ASSETS
#define H_ASSETS
#include "headers.h"

namespace Texture {
  SDL_Texture* load(const char*, SDL_Renderer*);
  void render(SDL_Texture*, SDL_Renderer*, int, int, int, int);
  void render(SDL_Texture*, SDL_Renderer*, int, int);
  void render(SDL_Texture*, SDL_Renderer*, SDL_Rect);
  void render(SDL_Texture*, SDL_Renderer*, SDL_Rect, SDL_Rect);
}

#endif
