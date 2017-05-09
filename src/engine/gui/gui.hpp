#ifndef H_ENGINE_GUI
#define H_ENGINE_GUI

#include "../constants.h"
#include "../sdl.h"
#include "../config/config.hpp"
#include "kiss_sdl.h"

namespace Engine {
  namespace Gui {
    class CGui {
      public:
        CGui();
        ~CGui() {};
        void Cleanup();
        int Init(SDL_Renderer **renderer);
        kiss_array objects;
    };
  }
}

#endif
