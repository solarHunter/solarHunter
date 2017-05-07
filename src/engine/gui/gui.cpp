#include <iostream>

#include "gui.hpp"
#include "../constants.h"

Engine::Gui::CGui::CGui() {}

void Engine::Gui::CGui::Cleanup() {
  kiss_clean(&this -> objects);
  std::cout << "GUI Cleanup" << std::endl;
}

int Engine::Gui::CGui::Init(SDL_Renderer **renderer, Engine::Configuration::CConfiguration *conf) {
  int resolution_x = atoi(conf -> Options["resolution_x"].c_str());
  int resolution_y = atoi(conf -> Options["resolution_y"].c_str());

  if (kiss_init(renderer, &this -> objects, resolution_x, resolution_y)) {
    std::cout << "ERROR loading kiss_sdl" << std::endl;
    return 1;
  }
  return 0;
}
