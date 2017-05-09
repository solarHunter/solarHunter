#include <iostream>

#include "gui.hpp"
#include "../constants.h"

Engine::Gui::CGui::CGui() {}

void Engine::Gui::CGui::Cleanup() {
  kiss_clean(&this -> objects);
  std::cout << "GUI Cleanup" << std::endl;
}

int Engine::Gui::CGui::Init(SDL_Renderer **renderer) {
  if (kiss_init(renderer, &this -> objects)) {
    std::cout << "ERROR loading kiss_sdl" << std::endl;
    return 1;
  }
  return 0;
}
