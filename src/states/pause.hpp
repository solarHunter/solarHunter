#ifndef H_STATES_PAUSE
#define H_STATES_PAUSE
#include "../engine/engine.hpp"

class PauseScene : public Engine::State::CState {
  public:
    void Init();
    void Cleanup();

    void Pause() {};
    void Resume() {};

    void HandleEvents(Engine::State::CStateEngine* state);
    void Draw(Engine::State::CStateEngine* state);
    void Update(Engine::State::CStateEngine *state) {};

    static PauseScene* Instance() {
      return &m_pausescene;
    }

  protected:
    PauseScene() {}

  private:
    static PauseScene m_pausescene;
    kiss_array objects;
    kiss_window window;
    kiss_label label = {0};
    kiss_button button_resume = {0}, button_exit = {0};
    char *message = (char*)"PAUSE\0";
    int draw = 1;

    void button_resume_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state);
    void button_exit_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state);
};

#endif
