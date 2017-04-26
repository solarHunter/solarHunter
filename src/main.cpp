#include <time.h>

#include "headers.h"
#include "utils.h"

#include "wrappers/renderer.hpp"

int main() {
  srand(time(NULL));

  SDL_Window *win = nullptr;
  if (utils::initializeSDL(&win) != 0) {
    SDL_DestroyWindow(win);
    utils::quitSDL();
    return 0;
  }

  wrapper::Renderer ren(&win);
  SDL_Texture *grid = ren.loadTexture("./media/grid.png");

  unsigned int now = SDL_GetPerformanceCounter();
  unsigned int last = 0;
  double deltatime = 0;

  unsigned int x = 0;
  SDL_Event e;
  bool running = true;
  while (running) {
    while(SDL_PollEvent(&e)){
      if (e.type == SDL_QUIT) {running = false;}
      if (e.type == SDL_KEYDOWN){
        switch (e.key.keysym.scancode) {
          case 41:
            running = false;
            break;
        }
      }
    }

    last = now;
    now = SDL_GetPerformanceCounter();
    deltatime = (double)((now - last) * 1000 / SDL_GetPerformanceFrequency());

    x += 1 * deltatime;
    if (x > 1020) x = 0;

    ren.clear();
    ren.renderTexture(grid, x - 1020, 0);
    ren.renderTexture(grid, x, 0);
    ren.present();
  }
  
  SDL_DestroyWindow(win);
  utils::quitSDL();

  return 0;
}
