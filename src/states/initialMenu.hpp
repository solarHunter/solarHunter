#ifndef H_STATES_INITIALMENU
#define H_STATES_INITIALMENU
#include "../engine/engine.hpp"
#include <iostream>

class InitialMenuScene : public Engine::State::CState {
  public:
    void Init();
    void Cleanup();

    void Pause() {};
    void Resume() {};

    void HandleEvents(Engine::State::CStateEngine* state);
    void Draw(Engine::State::CStateEngine* state);
    void Update(Engine::State::CStateEngine *state) {};

    static InitialMenuScene* Instance() {
      return &m_initialmenuscene;
    }

  protected:
    InitialMenuScene() {}

  private:
    static InitialMenuScene m_initialmenuscene;
    int background;
    kiss_window window;
    kiss_label label = {0};
    kiss_button button_ini = {0}, button_exit = {0};
    char *message = (char*)"SolarHunter " VERSION "\0";
    int draw = 1;

    void button_ini_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state);
    void button_exit_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state);
};

#endif
