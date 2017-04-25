#include "assets.h"

SDL_Texture* Texture::load(const char *src, SDL_Renderer *ren) {
  SDL_Texture* texture = nullptr;

  texture = IMG_LoadTexture(ren, src);
  if (texture == nullptr){
    std::cout << "ERROR::IMG_LoadTexture: " << SDL_GetError() << std::endl;
    return NULL;
  }
  return texture;
}

void Texture::render(SDL_Texture *texture, SDL_Renderer *ren, int x, int y, int w, int h) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;

  SDL_RenderCopy(ren, texture, NULL, &dest);
}

void Texture::render(SDL_Texture *texture, SDL_Renderer *ren, int x, int y) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(ren, texture, NULL, &dest);
}

void Texture::render(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dest) {
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Texture::render(SDL_Texture *texture, SDL_Renderer *ren, SDL_Rect section, SDL_Rect dest) {
  SDL_RenderCopy(ren, texture, &section, &dest);
}
