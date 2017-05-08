#include <iostream>
#include "engine.hpp"
CrunchEngine Crunch;

CrunchEngine::CrunchEngine() : Configuration(), Graphics(), State(), Gui(), Audio() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
    std::cout << "ERROR::SDL_Init: " << SDL_GetError() << std::endl;
    throw;
  }

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if(!(IMG_Init(imgFlags) & imgFlags)){
    std::cout << "ERROR::IMG_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this -> window);
    SDL_Quit();
    throw;
  }

  if(TTF_Init() != 0){
    std::cout << "ERROR::TTF_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this -> window);
    IMG_Quit();
    SDL_Quit();
    throw;
  }

  int resolution_x = atoi(this -> Configuration.Options["resolution_x"].c_str());
  int resolution_y = atoi(this -> Configuration.Options["resolution_y"].c_str());

  this -> screen_width = resolution_x;
  this -> screen_height = resolution_y;

  this -> window = SDL_CreateWindow(
      WINDOW_NAME,
      WINDOW_X,
      WINDOW_Y,
      resolution_x,
      resolution_y,
      SDL_WINDOW_SHOWN);
  if (!this -> window || this -> window == NULL){
    std::cout << "ERROR::SDL_CreateWindow: " << SDL_GetError() << std::endl; SDL_Quit();
    throw;
  }

  if (this -> Graphics.Init(&this -> window, &Configuration) != 0) {
    std::cout << "ERROR initializing graphics " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this -> window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    throw;
  }
  int fullscreen = atoi(this -> Configuration.Options["fullscreen"].c_str());
  if (fullscreen) {
    this -> Graphics.setFullscreen(1);
  }

  if (this -> Gui.Init(&this -> Graphics.renderer, &Configuration) != 0) {
    std::cout << "ERROR initializing graphics " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(this -> window);
    IMG_Quit();
    TTF_Quit();
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
