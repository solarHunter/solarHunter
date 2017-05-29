#ifndef H_STATES_ROOMSCENE
#define H_STATES_ROOMSCENE

#include "../engine/engine.hpp"
#include "../entities/player.hpp"
#include "../entities/camera.hpp"

class RoomScene : public Engine::State::CState {
  public:
    void Init();
    void Cleanup() {};

    void Pause() {};
    void Resume() {};

    void HandleEvents(Engine::State::CStateEngine* game);
    void Draw(Engine::State::CStateEngine* game);
    void Update(Engine::State::CStateEngine *game);

    static RoomScene* Instance() {
      return &m_roomscene;
    }

  protected:
    RoomScene() {}

  private:
    static RoomScene m_roomscene;
    int background;
    int x, y, width, height;
    CPlayer player;
    CCamera camera;
};

#endif
