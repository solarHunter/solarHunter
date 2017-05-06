#include "../engine/engine.hpp"

#include <iostream>
#include <cmath>

#include "test.hpp"

TestScene TestScene::m_testscene;
void TestScene::Init() {
  std::cout << "Generated TestScene" << std::endl;
  stars = Crunch.Graphics.Textures.Load("./media/stars.png");
  spaceship = Crunch.Graphics.Textures.Load("./media/spaceship.png");

  playerX = WINDOW_W / 2 - 30;
  playerY = WINDOW_H / 2 - 45;
};

void TestScene::HandleEvents(Engine::State::CStateEngine* game) {
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

void TestScene::Draw(Engine::State::CStateEngine* game) {
  Crunch.Graphics.Clear();

  Crunch.Graphics.Textures.Draw(stars, this -> x - 600, this -> y - 600);
  Crunch.Graphics.Textures.Draw(spaceship, playerX, playerY, 20, 40, playerRotation);


  Crunch.Graphics.Present();
};

void TestScene::Update(Engine::State::CStateEngine *game) {
  SDL_GetMouseState(&cursorX, &cursorY);
  dxRotation = cursorX - playerX;
  dyRotation = cursorY - playerY;
  playerRotation = (atan2(dxRotation, -dyRotation)) * 180 / PI;
}
