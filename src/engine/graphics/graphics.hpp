#ifndef H_GRAPHICS_ENGINE
#define H_GRAPHICS_ENGINE

#include <vector>

#include "../config/config.hpp"
#include "../mediamanager/mediamanager.hpp"
#include "../constants.h"
#include "../sdl.h"

namespace Engine {
  namespace Graphics {

    class CTexture {
      public:
        CTexture();
        ~CTexture();
        void Init(SDL_Renderer **renderer, Engine::Media::ImageList *images);

        int Load(const char *path);
        void Draw(int id);
        void Draw(int id, int x, int y);
        void Draw(int id, int x, int y, int w, int h);
        void Draw(int id, int x, int y, int w, int h, double angle);
      private:
        SDL_Renderer *renderer;
        Engine::Media::ImageList *images;
        std::vector<SDL_Texture*> textures;
    };

    class CGraphics {
      public:
        SDL_Renderer *renderer;
        SDL_Window **window;
        CGraphics();
        ~CGraphics();

        int Init(SDL_Window **window, Engine::Configuration::CConfiguration *conf, Engine::Media::ImageList *images);
        void setFullscreen(int f);
        void Present();
        void Clear();
        CTexture Textures;
    };

  }
}
#endif
