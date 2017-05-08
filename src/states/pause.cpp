#include "../engine/engine.hpp"

#include "pause.hpp"
#include "initialMenu.hpp"

PauseScene PauseScene::m_pausescene;
void PauseScene::button_resume_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state) {
  if (kiss_button_event(button, e, draw)) {
    state -> PopState();
  }
}

void PauseScene::button_exit_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state) {
  if (kiss_button_event(button, e, draw)) {
    state -> ChangeState(InitialMenuScene::Instance());
  }
}

void PauseScene::Init() {
  std::cout << "Pause start" << std::endl;
  kiss_window_new(
      &window, NULL, 0, 0, 0,
      atoi(Crunch.Configuration.Options["resolution_x"].c_str()),
      atoi(Crunch.Configuration.Options["resolution_y"].c_str())
      );

  kiss_label_new(
      &label, &window, message,
      (window.rect.w / 2) - strlen(message) * kiss_textfont.advance / 2,
      (window.rect.h / 3)
      );
  label.textcolor.r = 255;
  label.textcolor.g = 255;
  label.textcolor.b = 255;

  kiss_button_new(
      &button_resume, &window, (char*)"RESUME",
      window.rect.w / 2 - kiss_normal.w / 2,
      label.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );

  kiss_button_new(
      &button_exit, &window, (char*)"SALIR",
      window.rect.w / 2 - kiss_normal.w / 2,
      button_resume.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );

  window.visible = 1;
};

void PauseScene::Cleanup() {
  std::cout << "Pause cleanup" << std::endl;
};

void PauseScene::HandleEvents(Engine::State::CStateEngine* state) {
  kiss_window_event(&window, &state -> event, &draw);
  button_resume_event(&button_resume, &state -> event, &draw, state);
  button_exit_event(&button_exit, &state -> event, &draw, state);
};

void PauseScene::Draw(Engine::State::CStateEngine* state) {
  if (draw) {
    Crunch.Graphics.Clear();
    // kiss_window_draw(&window, Crunch.Graphics.renderer);
    kiss_label_draw(&label, Crunch.Graphics.renderer);
    kiss_button_draw(&button_resume, Crunch.Graphics.renderer);
    kiss_button_draw(&button_exit, Crunch.Graphics.renderer);
    draw = 0;
    Crunch.Graphics.Present();
  }
};
