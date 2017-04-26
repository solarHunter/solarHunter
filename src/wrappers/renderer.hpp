#ifndef H_WRAPPERS_RENDERER
#define H_WRAPPERS_RENDERER

  #include "../headers.h"

  #include <iostream>
  #include <vector>

namespace wrapper {
  class Renderer {
    SDL_Window **win;
    SDL_Renderer *ren;
    std::vector<SDL_Texture*> textures;

    public:
      Renderer(SDL_Window **win);
      ~Renderer();

      SDL_Texture *loadTexture(const char *path);
      SDL_Texture *loadTexture(SDL_Texture *texture);
      void renderTexture(SDL_Texture*, SDL_Rect, SDL_Rect);
      void renderTexture(SDL_Texture*, SDL_Rect);
      void renderTexture(SDL_Texture*, int, int, int, int);
      void renderTexture(SDL_Texture*, int, int);

      SDL_Renderer *getRenderer();
      void clear();
      void present();
  };
}

#endif
