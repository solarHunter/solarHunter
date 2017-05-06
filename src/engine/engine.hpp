#ifndef H_ENGINE
#define H_ENGINE

#include "graphics/graphics.hpp"
#include "state/stateEngine.hpp"
#include "gui/gui.hpp"
#include "config/config.hpp"

class CrunchEngine {
  public:
    CrunchEngine() : Configuration(), Graphics(), State(), Gui() {
      this -> Graphics.Init(&Configuration);
      this -> Gui.Init(&this -> Graphics.renderer, &Configuration);
    };
    Engine::Configuration::CConfiguration Configuration;
    Engine::Graphics::CGraphics Graphics;
    Engine::State::CStateEngine State;
    Engine::Gui::CGui Gui;
};
extern CrunchEngine Crunch;

#endif
