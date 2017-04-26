#include "headers.h"
#include "utils.h"

int utils::randI32(const int min, const int max) {
  return rand() % (max - min) + min;
}

int utils::initializeSDL(SDL_Window **win) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "ERROR::SDL_Init: " << SDL_GetError() << std::endl;
    return 1;
  }

  *win = SDL_CreateWindow(
      WINDOW_NAME,
      WINDOW_X,
      WINDOW_Y,
      WINDOW_W,
      WINDOW_H,
      SDL_WINDOW_SHOWN);
  if (*win == NULL){
    std::cout << "ERROR::SDL_CreateWindow: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if(!(IMG_Init(imgFlags) & imgFlags)){
    std::cout << "ERROR::IMG_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(*win);
    SDL_Quit();
    return 1;
  }

  if(TTF_Init() != 0){
    std::cout << "ERROR::TTF_Init: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(*win);
    IMG_Quit();
    SDL_Quit();
    return 1;
  }

  return 0;
}

void utils::quitSDL(void) {
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}
