#include <iostream>
#include "graphics.hpp"

Engine::Graphics::CGraphics::CGraphics() : Textures(){}

int Engine::Graphics::CGraphics::Init(SDL_Window **window, Engine::Configuration::CConfiguration *conf){

  int hwaccelerated = atoi(conf -> Options["hw_accelerated"].c_str());
  int vsync = atoi(conf -> Options["vsync"].c_str());

  unsigned int rendererFlags = 0;

  if (hwaccelerated) rendererFlags |= SDL_RENDERER_ACCELERATED;
  if (vsync) rendererFlags |= SDL_RENDERER_PRESENTVSYNC;

  this -> renderer = SDL_CreateRenderer(*window, -1, rendererFlags);
  if (!this -> renderer || this -> renderer == NULL) {
    std::cout << "No renderer " << SDL_GetError() << std::endl;
    return 1;
  }
  this -> Textures.Init(&renderer);

  std::cout << "Graphics::Init" << std::endl;
  return 0;
}

Engine::Graphics::CGraphics::~CGraphics() {
  SDL_DestroyRenderer(this -> renderer);
  std::cout << "Graphics::Cleanup" << std::endl;
}

void Engine::Graphics::CGraphics::Clear() {
  // SDL_SetRenderDrawColor(this -> renderer, 255, 255, 255, 255);
  SDL_SetRenderDrawColor(this -> renderer, 0, 0, 0, 255);
  SDL_RenderClear(this -> renderer);
}

void Engine::Graphics::CGraphics::Present() {
  SDL_RenderPresent(this -> renderer);
}
