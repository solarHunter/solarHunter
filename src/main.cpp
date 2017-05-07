#include "engine/engine.hpp"

#include "states/initialMenu.hpp"

int main() {
  Crunch.State.ChangeState(InitialMenuScene::Instance());

  while (Crunch.State.Running()) {
    Crunch.State.HandleEvents();
    Crunch.State.Update();
    Crunch.State.Draw();
  }
}
