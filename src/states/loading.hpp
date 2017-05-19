#ifndef H_STATES_LOADING
#define H_STATES_LOADING
#include "../engine/engine.hpp"
#include <iostream>

class LoadingScene : public Engine::State::CState {
  public:
    void Init();
    void Cleanup();

    void Pause() {};
    void Resume() {};

    void HandleEvents(Engine::State::CStateEngine* state) {};
    void Draw(Engine::State::CStateEngine* state);
    void Update(Engine::State::CStateEngine *state);

    static LoadingScene* Instance() {
      return &m_loadingscene;
    }

  protected:
    LoadingScene() {}

  private:
    static LoadingScene m_loadingscene;
};

#endif
