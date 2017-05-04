#ifndef H_ENGINE
#define H_ENGINE

#include "graphics/graphics.hpp"
#include "state/stateEngine.hpp"
#include "../engine/gui/kiss_sdl.h"

namespace Crunch {
  Engine::Graphics::CGraphics Graphics;
  Engine::State::CStateEngine State;
}

#endif
