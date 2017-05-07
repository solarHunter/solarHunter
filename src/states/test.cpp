#include "../engine/engine.hpp"

#include <iostream>
#include <cmath>

#include "test.hpp"
#include "pause.hpp"

TestScene TestScene::m_testscene;
void TestScene::Init() {
  std::cout << "Generated TestScene" << std::endl;
  stars = Crunch.Graphics.Textures.Load("./media/universe.jpg");
  spaceship = Crunch.Graphics.Textures.Load("./media/spaceship.png");

  playerX = Crunch.screen_width / 2 - 30;
  playerY = Crunch.screen_height / 2 - 45;
};

void TestScene::HandleEvents(Engine::State::CStateEngine* game) {
  if (game -> event.type == SDL_KEYDOWN){
    switch (game -> event.key.keysym.scancode) {
      case 41:
        // game -> Quit();
        game -> PushState(PauseScene::Instance());
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

  Crunch.Graphics.Textures.Draw(stars, this -> x, this -> y, Crunch.screen_width, Crunch.screen_height);
  Crunch.Graphics.Textures.Draw(spaceship, playerX, playerY, 66, 80, playerRotation);


  Crunch.Graphics.Present();
};

void TestScene::Update(Engine::State::CStateEngine *game) {
  SDL_GetMouseState(&cursorX, &cursorY);
  dxRotation = cursorX - playerX;
  dyRotation = cursorY - playerY;
  playerRotation = (atan2(dxRotation, -dyRotation)) * 180 / PI;
}
