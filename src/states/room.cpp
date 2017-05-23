#include "../engine/engine.hpp"

#include <iostream>
#include <cmath>

#include "room.hpp"
#include "pause.hpp"

RoomScene RoomScene::m_roomscene;
void RoomScene::Init() {
  background = Crunch.Graphics.Textures.Load("./media/universe-big.jpg");
  width = Crunch.screen_height*2.5;
  height = Crunch.screen_height*2.5;
};

void RoomScene::HandleEvents(Engine::State::CStateEngine* game) {
  if (game -> event.type == SDL_KEYDOWN){
    switch (game -> event.key.keysym.scancode) {
      case 41:
        game -> PushState(PauseScene::Instance());
        break;
      default: break;
    }
  }
  player.HandleEvents(game);
};

void RoomScene::Draw(Engine::State::CStateEngine* game) {
  Crunch.Graphics.Clear();

  Crunch.Graphics.Textures.Draw(background, this -> x, this -> y, Crunch.screen_width*2.5, Crunch.screen_height*2.5);
  //player.setCamera();
  player.Draw();

  Crunch.Graphics.Present();
};

void RoomScene::Update(Engine::State::CStateEngine *game) {
  player.Update(game);
}
