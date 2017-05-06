#ifndef H_ENGINE
#define H_ENGINE

#include "graphics/graphics.hpp"
#include "state/stateEngine.hpp"
#include "gui/gui.hpp"

class CrunchEngine {
  public:
    CrunchEngine() : Graphics(), State(), Gui() {
      this -> Gui.Init(&this -> Graphics.renderer);
    };
    Engine::Graphics::CGraphics Graphics;
    Engine::State::CStateEngine State;
    Engine::Gui::CGui Gui;
};
extern CrunchEngine Crunch;

#endif
