#ifndef H_ENGINE
#define H_ENGINE

#include "graphics/graphics.hpp"
#include "state/stateEngine.hpp"
#include "gui/gui.hpp"
#include "config/config.hpp"
#include "audio/audio.hpp"

class CrunchEngine {
  public:
    CrunchEngine();
    ~CrunchEngine();
    Engine::Configuration::CConfiguration Configuration;
    Engine::Graphics::CGraphics Graphics;
    Engine::State::CStateEngine State;
    Engine::Gui::CGui Gui;
    Engine::Audio::CAudio Audio;
    SDL_Window *window;
    int screen_width, screen_height;

  private:
    void Cleanup();
};

extern CrunchEngine Crunch;

#endif
