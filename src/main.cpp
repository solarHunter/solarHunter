#include "engine/engine.hpp"

// States
#include "states/test.hpp"

int main() {
  Crunch::State.ChangeState(TestScene::Instance());

  while (Crunch::State.Running()) {
    Crunch::State.HandleEvents();
    Crunch::State.Update();
    Crunch::State.Draw();
  }

  Crunch::State.Cleanup();
}
