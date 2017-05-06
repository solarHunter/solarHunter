#include <iostream>
#include "graphics.hpp"

Engine::Graphics::CGraphics::CGraphics() : Textures(){}

int Engine::Graphics::CGraphics::Init(Engine::Configuration::CConfiguration *conf){
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "ERROR::SDL_Init: " << SDL_GetError() << std::endl;
    return 1;
  }

  int resolution_x = atoi(conf -> Options["resolution_x"].c_str());
  int resolution_y = atoi(conf -> Options["resolution_y"].c_str());

  this -> screen_width = resolution_x;
  this -> screen_height = resolution_y;

  int hwaccelerated = atoi(conf -> Options["hw_accelerated"].c_str());
  int vsync = atoi(conf -> Options["vsync"].c_str());
  int fullscreen = atoi(conf -> Options["fullscreen"].c_str());


  this -> window = SDL_CreateWindow(
      WINDOW_NAME,
      WINDOW_X,
      WINDOW_Y,
      resolution_x,
      resolution_y,
      SDL_WINDOW_SHOWN);
  if (!this -> window || this -> window == NULL){
    std::cout << "ERROR::SDL_CreateWindow: " << SDL_GetError() << std::endl; SDL_Quit();
    return 1;
  }

  unsigned int rendererFlags = 0;

  if (hwaccelerated) rendererFlags |= SDL_RENDERER_ACCELERATED;
  if (vsync) rendererFlags |= SDL_RENDERER_PRESENTVSYNC;

  this -> renderer = SDL_CreateRenderer(this -> window, -1, rendererFlags);
  if (!this -> renderer){

    SDL_DestroyWindow(this -> window);
    SDL_Quit();
    return 1;
  }
  if (!this -> renderer || this -> renderer == NULL) {
    std::cout << "No renderer" << std::endl;
  }

  if (fullscreen) {
    SDL_SetWindowFullscreen(this -> window, SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(true);
  }

  this -> Textures.Init(&renderer);
  std::cout << "Graphics::renderer " << renderer << std::endl;

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if(!(IMG_Init(imgFlags) & imgFlags)){
    std::cout << "ERROR::IMG_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(this -> renderer);
    SDL_DestroyWindow(this -> window);
    SDL_Quit();
    return 1;
  }

  if(TTF_Init() != 0){
    std::cout << "ERROR::TTF_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(this -> renderer);
    SDL_DestroyWindow(this -> window);
    IMG_Quit();
    SDL_Quit();
    return 1;
  }
  std::cout << "Graphics::Init" << std::endl;
  return 0;
}

Engine::Graphics::CGraphics::~CGraphics() {
  SDL_DestroyRenderer(this -> renderer);
  SDL_DestroyWindow(this -> window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
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
