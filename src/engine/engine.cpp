#include <iostream>
#include "engine.hpp"

CrunchEngine::CrunchEngine() : Configuration(), Media(), Graphics(), State(), Gui(), Audio() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
    std::cout << "ERROR::SDL_Init: " << SDL_GetError() << std::endl;
    throw;
  }

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if(!(IMG_Init(imgFlags) & imgFlags)){
    std::cout << "ERROR::IMG_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this -> window);
    Mix_Quit();
    SDL_Quit();
    throw;
  }

  if(TTF_Init() != 0){
    std::cout << "ERROR::TTF_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this -> window);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    throw;
  }

  this -> screen_width = atoi(this -> Configuration.General["resolution_x"].c_str());
  this -> screen_height = atoi(this -> Configuration.General["resolution_y"].c_str());

  this -> window = SDL_CreateWindow(
      WINDOW_NAME,
      WINDOW_X,
      WINDOW_Y,
      this -> screen_width,
      this -> screen_height,
      SDL_WINDOW_SHOWN);
  if (!this -> window || this -> window == NULL){
    std::cout << "ERROR::SDL_CreateWindow: " << SDL_GetError() << std::endl; SDL_Quit();
    throw;
  }

  if (this -> Graphics.Init(&this -> window, &Configuration, &Media.images) != 0) {
    std::cout << "ERROR initializing graphics " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this -> window);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
    throw;
  }
  if (atoi(this -> Configuration.General["fullscreen"].c_str())) {
    this -> Graphics.setFullscreen(1);
  }

  if (this -> Gui.Init(&this -> Graphics.renderer) != 0) {
    std::cout << "ERROR initializing graphics " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this -> window);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
    throw;
  }
};

CrunchEngine::~CrunchEngine() {
  std::cout << "Stop engine" << std::endl;

  this -> State.Cleanup();
  this -> Gui.Cleanup();

  SDL_DestroyWindow(this -> window);
  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
  SDL_Quit();
}
