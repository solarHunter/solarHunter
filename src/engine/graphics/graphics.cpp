#include <iostream>
#include "graphics.hpp"

Engine::Graphics::CGraphics::CGraphics() : Textures(){
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "ERROR::SDL_Init: " << SDL_GetError() << std::endl;
    throw;
  }

  this -> window = SDL_CreateWindow(
      WINDOW_NAME,
      WINDOW_X,
      WINDOW_Y,
      WINDOW_W,
      WINDOW_H,
      SDL_WINDOW_SHOWN);
  if (!this -> window || this -> window == NULL){
    std::cout << "ERROR::SDL_CreateWindow: " << SDL_GetError() << std::endl; SDL_Quit();
    throw;
  }

  unsigned int rendererFlags = 0;
  if (HW_ACCELERATED) rendererFlags |= SDL_RENDERER_ACCELERATED;
  if (VSYNC) rendererFlags |= SDL_RENDERER_PRESENTVSYNC;

  this -> renderer = SDL_CreateRenderer(this -> window, -1, rendererFlags);
  if (!this -> renderer){

    SDL_DestroyWindow(this -> window);
    SDL_Quit();
    throw;
  }
  if (!this -> renderer || this -> renderer == NULL) {
    std::cout << "No renderer" << std::endl;
  }

  if (FULLSCREEN) {
    SDL_SetWindowFullscreen(this -> window, SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(true);
  }

  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  this -> screen_width = DM.w;
  this -> screen_height = DM.h;

  this -> Textures.Init(&renderer);
  std::cout << "Graphics::renderer " << renderer << std::endl;

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if(!(IMG_Init(imgFlags) & imgFlags)){
    std::cout << "ERROR::IMG_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(this -> renderer);
    SDL_DestroyWindow(this -> window);
    SDL_Quit();
    throw;
  }

  if(TTF_Init() != 0){
    std::cout << "ERROR::TTF_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(this -> renderer);
    SDL_DestroyWindow(this -> window);
    IMG_Quit();
    SDL_Quit();
    throw;
  }
  std::cout << "Graphics::Init" << std::endl;
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
