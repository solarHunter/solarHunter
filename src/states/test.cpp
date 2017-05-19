#include "../engine/engine.hpp"

#include <iostream>
#include <cmath>

#include "test.hpp"
#include "pause.hpp"

TestScene TestScene::m_testscene;
void TestScene::Init() {
  Engine::Media::MediaList list;
  list["gameBackground"] = "./media/universe.jpg";
  Crunch.Media.Load(&list, NULL);

  stars = Crunch.Graphics.Textures.Load("gameBackground");
};

void TestScene::HandleEvents(Engine::State::CStateEngine* game) {
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

void TestScene::Draw(Engine::State::CStateEngine* game) {
  Crunch.Graphics.Clear();

  Crunch.Graphics.Textures.Draw(stars, this -> x, this -> y, Crunch.screen_width, Crunch.screen_height);
  player.Draw();

  Crunch.Graphics.Present();
};

void TestScene::Update(Engine::State::CStateEngine *game) {
  player.Update(game);
}
