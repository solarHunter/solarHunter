#include "../engine/engine.hpp"

#include "initialMenu.hpp"
#include "test.hpp"

InitialMenuScene InitialMenuScene::m_initialmenuscene;
void InitialMenuScene::button_ini_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state) {
  if (kiss_button_event(button, e, draw)) {
    state -> ChangeState(TestScene::Instance());
  }
}

void InitialMenuScene::button_exit_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state) {
  if (kiss_button_event(button, e, draw)) {
    state -> Quit();
  }
}

void InitialMenuScene::Init() {
  std::cout << "Generated menuScene" << std::endl;

  kiss_window_new(&window, NULL, 0, 0, 0, WINDOW_W, WINDOW_H);

  kiss_label_new(
      &label, &window, message,
      (window.rect.w / 2) - strlen(message) * kiss_textfont.advance / 2,
      (window.rect.h / 3)
      );
  label.textcolor.r = 255;
  label.textcolor.g = 255;
  label.textcolor.b = 255;

  kiss_button_new(
      &button_ini, &window, (char*)"INICIAR",
      window.rect.w / 2 - kiss_normal.w / 2,
      label.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );

  kiss_button_new(
      &button_exit, &window, (char*)"SALIR",
      window.rect.w / 2 - kiss_normal.w / 2,
      button_ini.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );

  window.visible = 1;
};

void InitialMenuScene::Cleanup() {
  std::cout << "initialMenu cleanup" << std::endl;
};

void InitialMenuScene::HandleEvents(Engine::State::CStateEngine* state) {
  kiss_window_event(&window, &state -> event, &draw);
  button_ini_event(&button_ini, &state -> event, &draw, state);
  button_exit_event(&button_exit, &state -> event, &draw, state);
};

void InitialMenuScene::Draw(Engine::State::CStateEngine* state) {
  if (draw) {
    Crunch.Graphics.Clear();
    // kiss_window_draw(&window, Crunch.Graphics.renderer);
    kiss_label_draw(&label, Crunch.Graphics.renderer);
    kiss_button_draw(&button_ini, Crunch.Graphics.renderer);
    kiss_button_draw(&button_exit, Crunch.Graphics.renderer);
    draw = 0;
    Crunch.Graphics.Present();
  }
};
