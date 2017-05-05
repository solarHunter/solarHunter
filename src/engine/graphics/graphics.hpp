#ifndef H_GRAPHICS_ENGINE
#define H_GRAPHICS_ENGINE

#include <vector>

#include "../constants.h"
#include "../sdl.h"

namespace Engine {
  namespace Graphics {

    class CTexture {
      public:
        CTexture();
        ~CTexture();
        void Init(SDL_Renderer **renderer);

        int Load(const char *path);
        void Draw(int id);
        void Draw(int id, int x, int y);
        void Draw(int id, int x, int y, int w, int h);
        void Draw(int id, int x, int y, int w, int h, double angle);
      private:
        SDL_Renderer *renderer;
        std::vector<SDL_Texture*> textures;
    };

    class CGraphics {
      public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        CGraphics();
        ~CGraphics();
        void Present();
        void Clear();
        CTexture Textures;
    };

  }
}
#endif
