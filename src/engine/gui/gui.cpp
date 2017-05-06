#include <iostream>

#include "gui.hpp"
#include "../constants.h"

Engine::Gui::CGui::CGui() {}

Engine::Gui::CGui::~CGui() {
  kiss_clean(&this -> objects);
  std::cout << "GUI Cleanup" << std::endl;
}

int Engine::Gui::CGui::Init(SDL_Renderer **renderer) {
  if (kiss_init(renderer, &this -> objects, WINDOW_W, WINDOW_H)) {
    std::cout << "ERROR loading kiss_sdl" << std::endl;
    return 1;
  }
  return 0;
}
