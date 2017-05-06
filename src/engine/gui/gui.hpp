#include "../sdl.h"
#include "kiss_sdl.h"

namespace Engine {
  namespace Gui {
    class CGui {
      public:
        CGui();
        ~CGui();
        int Init(SDL_Renderer **renderer);
        kiss_array objects;
    };
  }
}
