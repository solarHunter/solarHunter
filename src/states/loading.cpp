#include "../engine/engine.hpp"
#include "loading.hpp"
#include "initialMenu.hpp"

LoadingScene LoadingScene::m_loadingscene;

void LoadingScene::Init() {
  Engine::Media::MediaList list;
  list["initialBackground"] = "./media/background.jpg";
  list["gameBackground"] = "./media/universe.jpg";
  list["ship"] = "./media/spaceship.png";

  Crunch.Media.Load(&list, NULL);
  Crunch.State.ChangeState(InitialMenuScene::Instance());
}
void LoadingScene::Cleanup() {}
void LoadingScene::Draw(Engine::State::CStateEngine* state) {}
void LoadingScene::Update(Engine::State::CStateEngine *state) {};
