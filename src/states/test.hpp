#ifndef H_STATES_TESTSCENE
#define H_STATES_TESTSCENE

#include "../engine/engine.hpp"
#include "../entities/player.hpp"

class TestScene : public Engine::State::CState {
  public:
    void Init();
    void Cleanup() {};

    void Pause() {};
    void Resume() {};

    void HandleEvents(Engine::State::CStateEngine* game);
    void Draw(Engine::State::CStateEngine* game);
    void Update(Engine::State::CStateEngine *game);

    static TestScene* Instance() {
      return &m_testscene;
    }

  protected:
    TestScene() {}

  private:
    static TestScene m_testscene;
    int stars;
    int x, y;
    CPlayer player;
};

#endif
