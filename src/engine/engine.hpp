#ifndef H_ENGINE
#define H_ENGINE

#include "graphics/graphics.hpp"
#include "state/stateEngine.hpp"
#include "../engine/gui/kiss_sdl.h"

class CrunchEngine {
  public:
    CrunchEngine() : Graphics(), State() {};
    Engine::Graphics::CGraphics Graphics;
    Engine::State::CStateEngine State;
};
extern CrunchEngine Crunch;

#endif
