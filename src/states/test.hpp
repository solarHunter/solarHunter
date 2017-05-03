#include "../engine/engine.hpp"
#include <iostream>

class TestScene : public Engine::State::CState {
  public:
    void Init() {
      grid = Crunch::Graphics.Textures.Load("./media/grid.png");
      spaceship = Crunch::Graphics.Textures.Load("./media/spaceship.png");
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
            this -> y += 2;
            break;
          case 7:
            this -> x -= 2;
            break;
          case 22:
            this -> y -= 2;
            break;
          case 4:
            this -> x += 2;
            break;
          default:
            std::cout << "Input: " << game -> event.key.keysym.scancode << std::endl;
            break;
        }
      }
    };

    void Draw(Engine::State::CStateEngine* game) {
      Crunch::Graphics.Clear();

      Crunch::Graphics.Textures.Draw(grid, this -> x, this -> y, WINDOW_W, WINDOW_H);
      Crunch::Graphics.Textures.Draw(spaceship, WINDOW_W / 2 - 30, WINDOW_H / 2 - 45, 60, 90);

      Crunch::Graphics.Present();
    };

    void Update(Engine::State::CStateEngine *game) {}

    static TestScene* Instance() {
      return &m_testscene;
    }

  protected:
    TestScene() {}

  private:
    static TestScene m_testscene;
    int grid, spaceship;
    int x, y;
};
TestScene TestScene::m_testscene;
