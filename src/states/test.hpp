#include "../engine/engine.hpp"
#include <iostream>

class TestScene : public Engine::State::CState {
  public:
    void Init() {
      grid = Crunch::Graphics.Textures.Load("./media/grid.png");
    };
    void Cleanup() {};

    void Pause() {};
    void Resume() {};

    void HandleEvents(Engine::State::CStateEngine* game) {
      if (game -> event.type == SDL_KEYDOWN){
        switch (game -> event.key.keysym.scancode) {
          case 41:
            game -> Quit();
            break;
          case 26:
            std::cout << "W!!" << std::endl;
            break;
          case 7:
            std::cout << "D!!" << std::endl;
            break;
          case 22:
            std::cout << "S!!" << std::endl;
            break;
          case 4:
            std::cout << "A!!" << std::endl;
            break;
          default:
            std::cout << "Input: " << game -> event.key.keysym.scancode << std::endl;
            break;
        }
      }
    };

    void Draw(Engine::State::CStateEngine* game) {
      Crunch::Graphics.Clear();
      Crunch::Graphics.Textures.Draw(grid, 0, 0, 300, 300);
      Crunch::Graphics.Present();
    };

    void Update(Engine::State::CStateEngine *game) {
    }

    static TestScene* Instance() {
      return &m_testscene;
    }

  protected:
    TestScene() {}

  private:
    static TestScene m_testscene;
    int grid;
};
TestScene TestScene::m_testscene;
