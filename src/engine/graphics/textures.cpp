#include <vector>
#include <iostream>

#include "graphics.hpp"

Engine::Graphics::CTexture::CTexture() {
  std::cout << "Textures::Init" << std::endl;
}

Engine::Graphics::CTexture::~CTexture() {
  while (!this -> textures.empty()) {
    SDL_DestroyTexture(this -> textures.back());
    this -> textures.pop_back();
  }

  std::cout << "Textures::Cleanup " << this -> textures.size() << " textures remaining" << std::endl;
}

void Engine::Graphics::CTexture::Init(SDL_Renderer **renderer) {
  this -> renderer = *renderer;
  if (!this -> renderer || this -> renderer == NULL) {
    std::cout << "No renderer" << std::endl;
  }
  std::cout << "Textures::renderer " << this -> renderer << std::endl;
}

int Engine::Graphics::CTexture::Load(const char *path) {
  SDL_Texture* texture = nullptr;
  texture = IMG_LoadTexture(renderer, path);
  if (!texture || texture == NULL){
    std::cout << "ERROR::IMG_LoadTexture: " << SDL_GetError() << std::endl;
    SDL_DestroyTexture(texture);
    return -1;
  }

  this -> textures.push_back(texture);
  std::cout << "Textures::Load " << texture << std::endl;
  return (int)(this -> textures.size() - 1);
}

void Engine::Graphics::CTexture::Draw(int id, int x, int y, int w, int h) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;

  SDL_RenderCopy(renderer, this -> textures[id], NULL, &dest);
}

void Engine::Graphics::CTexture::Draw(int id, int x, int y) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(this -> textures[id], NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(this -> renderer, this -> textures[id], NULL, &dest);
}

void Engine::Graphics::CTexture::Draw(int id) {
  SDL_Rect dest;
  dest.x = 0;
  dest.y = 0;
  SDL_QueryTexture(this -> textures[id], NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(this -> renderer, this -> textures[id], NULL, &dest);
}
