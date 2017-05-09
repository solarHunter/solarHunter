#include "engine/engine.hpp"
const char *Engine::Path::configuration_file = "./solarhunter.conf";
CrunchEngine Crunch;

#include "states/initialMenu.hpp"

int main() {
  Crunch.Audio.LoadBacktrack("./media/audio/backtrack.mp3");
  Crunch.State.ChangeState(InitialMenuScene::Instance());

  while (Crunch.State.Running()) {
    Crunch.State.HandleEvents();
    Crunch.State.Update();
    Crunch.State.Draw();
  }
}
