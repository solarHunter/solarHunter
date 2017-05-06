#ifndef H_ENGINE_GUI
#define H_ENGINE_GUI

#include "../sdl.h"
#include "../config/config.hpp"
#include "kiss_sdl.h"

namespace Engine {
  namespace Gui {
    class CGui {
      public:
        CGui();
        ~CGui();
        int Init(SDL_Renderer **renderer, Engine::Configuration::CConfiguration *conf);
        kiss_array objects;
    };
  }
}

#endif
