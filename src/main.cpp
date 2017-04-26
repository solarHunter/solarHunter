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

  ren.clear();
  ren.renderTexture(grid, 0, 0, WINDOW_W, WINDOW_H);
  ren.present();

  SDL_Delay(5000);
  
  SDL_DestroyWindow(win);
  utils::quitSDL();

  return 0;
}
