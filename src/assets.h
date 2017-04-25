#ifndef H_ASSETS
#define H_ASSETS
#include "headers.h"

namespace Texture {
  SDL_Texture* load(const char*, SDL_Renderer*);
  void render(SDL_Texture*, SDL_Renderer*, int, int, int, int);
  void render(SDL_Texture *texture, SDL_Renderer *ren, int x, int y);
  void render(SDL_Texture*, SDL_Renderer*, SDL_Rect);
  void render(SDL_Texture *texture, SDL_Renderer *ren, SDL_Rect section, SDL_Rect dest);
}

#endif
