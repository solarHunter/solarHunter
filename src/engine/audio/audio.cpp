#include <iostream>
#include "audio.hpp"

Engine::Audio::CAudio::CAudio() {
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cout << "ERROR: " << Mix_GetError() << std::endl;
    throw;
  }
}

Engine::Audio::CAudio::~CAudio() {
  Mix_FreeMusic(this -> backtrack);
}

void Engine::Audio::CAudio::StopBacktrack() {
  if (Mix_PlayingMusic() == 0) {
    Mix_HaltMusic();
  }
}

int Engine::Audio::CAudio::LoadBacktrack(const char *path) {
  StopBacktrack();
  this -> backtrack = Mix_LoadMUS(path);
  if(!this -> backtrack || this -> backtrack == NULL) {
    std::cout << "Error loading backtrack: " << Mix_GetError() << std::endl;
    return 1;
  }
  Mix_PlayMusic(this -> backtrack, -1);
  return 0;
}
