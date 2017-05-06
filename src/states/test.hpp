#ifndef H_STATES_TESTSCENE
#define H_STATES_TESTSCENE

#include "../engine/engine.hpp"
#include <iostream>
#include "initialMenu.hpp"
#include <cmath>

const float PI = 3.14159265;

class TestScene : public Engine::State::CState {
  public:
    void Init() {
      std::cout << "Generated TestScene" << std::endl;
      stars = Crunch.Graphics.Textures.Load("./media/stars.png");
      spaceship = Crunch.Graphics.Textures.Load("./media/spaceship.png");

      playerX = WINDOW_W / 2 - 30;
      playerY = WINDOW_H / 2 - 45;
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
            this -> playerY -= 4;
            //this -> playerRotation = 0;
            break;
          case 7:
            this -> playerX += 4;
            //this -> playerRotation = 90;
            break;
          case 22:
            this -> playerY += 4;
            //this -> playerRotation = 180;
            break;
          case 4:
            this -> playerX -= 4;
            //this -> playerRotation = 270;
            break;
          default:
            std::cout << "Input: " << game -> event.key.keysym.scancode << std::endl;
            break;
        }
      }
    };

    void Draw(Engine::State::CStateEngine* game) {
      Crunch.Graphics.Clear();

      Crunch.Graphics.Textures.Draw(stars, this -> x - 600, this -> y - 600);
      Crunch.Graphics.Textures.Draw(spaceship, playerX, playerY, 20, 40, playerRotation);


      Crunch.Graphics.Present();
    };

    void Update(Engine::State::CStateEngine *game) {
      SDL_GetMouseState(&cursorX, &cursorY);
      dxRotation = cursorX - playerX;
      dyRotation = cursorY - playerY;
      playerRotation = (atan2(dxRotation, -dyRotation)) * 180 / PI;
    }

    static TestScene* Instance() {
      return &m_testscene;
    }

  protected:
    TestScene() {}

  private:
    static TestScene m_testscene;
    int stars, spaceship;
    int x, y;
    int playerX;
    int playerY;
    int cursorX;
    int cursorY;
    int playerRotation;
    float dxRotation;
    float dyRotation;
};
TestScene TestScene::m_testscene;

#endif
