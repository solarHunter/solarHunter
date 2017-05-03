#include "stateEngine.hpp"

#include <iostream>

void Engine::State::CStateEngine::Init() {
  std::cout << "StateEngine::Init" << std::endl;
}

void Engine::State::CStateEngine::Cleanup() {
  while (!this -> states.empty()) {
    this -> states.back()->Cleanup();
    this -> states.pop_back();
  }
  std::cout << "StateEngine::Cleanup" << std::endl;
}

void Engine::State::CStateEngine::ChangeState(Engine::State::CState* state) {
  if (!this -> states.empty()) {
    this -> states.back()->Cleanup();
    this -> states.pop_back();
  }

  this -> states.push_back(state);
  this -> states.back()->Init();
}

void Engine::State::CStateEngine::PushState(State::CState* state) {
  if (!this -> states.empty()) {
    this -> states.back() -> Pause();
  }

  this -> states.push_back(state);
  this -> states.back() -> Init();
}

void Engine::State::CStateEngine::PopState() {
  if (!this -> states.empty()) {
    this -> states.back() -> Cleanup();
    this -> states.pop_back();
  }

  if (!this -> states.empty()) {
    this -> states.back() -> Resume();
  }
}


void Engine::State::CStateEngine::HandleEvents() {
  while (SDL_PollEvent(&this -> event)) {
    if (this -> event.type == SDL_QUIT) { this -> Quit(); }
    this -> states.back() -> HandleEvents(this);
  }
  // this -> states.back() -> HandleEvents(this);
}

void Engine::State::CStateEngine::Update() {
  this -> states.back() -> Update(this);
}

void Engine::State::CStateEngine::Draw() {
  this -> states.back() -> Draw(this);
}
