#include "renderer.hpp"

wrapper::Renderer::Renderer(SDL_Window **win) {
  this -> win = win;
  if (!this -> win){
    std::cout << "ERROR::SDL_NoWindow: " << SDL_GetError() << std::endl;
    throw;
  }

  unsigned int rendererFlags = 0;
  if (HW_ACCELERATED) rendererFlags |= SDL_RENDERER_ACCELERATED;
  if (VSYNC) rendererFlags |= SDL_RENDERER_PRESENTVSYNC;

  this -> ren = SDL_CreateRenderer(*this -> win, -1, rendererFlags);
  if (!this -> ren){
    std::cout << "ERROR::SDL_CreateRenderer: " << SDL_GetError() << std::endl;
    throw;
  }
}

wrapper::Renderer::~Renderer() {
  for (std::vector<SDL_Texture*>::iterator t = this -> textures.begin(); t != this -> textures.end(); ++t) {
    if (*t) SDL_DestroyTexture(*t);
  }

  SDL_DestroyRenderer(this -> ren);
  std::cout << "Renderer::Destructor()" << std::endl;
}

SDL_Texture *wrapper::Renderer::loadTexture(const char *path) {
  SDL_Texture* texture = nullptr;

  texture = IMG_LoadTexture(this -> ren, path);
  if (!texture){
    std::cout << "ERROR::IMG_LoadTexture: " << SDL_GetError() << std::endl;
    SDL_DestroyTexture(texture);
    return nullptr;
  }

  this -> textures.push_back(texture);
  return texture;
}

SDL_Texture *wrapper::Renderer::loadTexture(SDL_Texture *texture) {
  this -> textures.push_back(texture);
  return texture;
}

void wrapper::Renderer::renderTexture(SDL_Texture *texture, int x, int y, int w, int h) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;

  SDL_RenderCopy(this -> ren, texture, NULL, &dest);
}

void wrapper::Renderer::renderTexture(SDL_Texture *texture, int x, int y) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(this -> ren, texture, NULL, &dest);
}

void wrapper::Renderer::renderTexture(SDL_Texture *texture, SDL_Rect dest) {
  SDL_RenderCopy(this -> ren, texture, NULL, &dest);
}

void wrapper::Renderer::renderTexture(SDL_Texture *texture, SDL_Rect section, SDL_Rect dest) {
  SDL_RenderCopy(this -> ren, texture, &section, &dest);
}

SDL_Renderer *wrapper::Renderer::getRenderer() {
  return this -> ren;
}

void wrapper::Renderer::clear() {
  SDL_SetRenderDrawColor(this -> ren, 255, 255, 255, 255);
  SDL_RenderClear(this -> ren);
}

void wrapper::Renderer::present() {
  SDL_RenderPresent(this -> ren);
}
