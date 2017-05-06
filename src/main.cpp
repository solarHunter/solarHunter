#include "engine/engine.hpp"
CrunchEngine Crunch;

#include "states/initialMenu.hpp"

int main() {
  Crunch.State.ChangeState(InitialMenuScene::Instance());

  while (Crunch.State.Running()) {
    Crunch.State.HandleEvents();
    Crunch.State.Update();
    Crunch.State.Draw();
  }

  Crunch.State.Cleanup();
}
