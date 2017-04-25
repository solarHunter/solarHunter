#include <time.h>

#include "headers.h"
#include "utils.h"
#include "assets.h"

int main() {
  srand(time(NULL));

  SDL_Window *win = nullptr;
  SDL_Renderer *ren = nullptr;
  if (utils::initializeSDL(&win, &ren) != 0) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    utils::quitSDL();
    return 0;
  }

  SDL_Texture *grid = Texture::load("./media/grid.png", ren);

  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderClear(ren);

  Texture::render(grid, ren, 0, 0, WINDOW_W, WINDOW_H);

  SDL_RenderPresent(ren);
  SDL_Delay(5000);
  
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  utils::quitSDL();

  return 0;
}
