#ifndef H_STATES_INITIALMENU
#define H_STATES_INITIALMENU

#include "../engine/engine.hpp"
#include <iostream>

#include "test.hpp"

void button_ini_event(kiss_button *button, SDL_Event *e, int *draw) {
  if (kiss_button_event(button, e, draw)) {
    Crunch::State.ChangeState(TestScene::Instance());
  }
}

void button_exit_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* game) {
  if (kiss_button_event(button, e, draw)) {
    game -> Quit();
  }
}

class InitialMenuScene : public Engine::State::CState {
  public:
    void Init() {
      std::cout << "Generated menuScene" << std::endl;
      kiss_array_new(&this -> objects);

      int err = kiss_init(&Crunch::Graphics.window, &Crunch::Graphics.renderer, &objects, 320, 120);
      if (err) std::cout << "ERROR loading kiss_sdl" << std::endl;

      kiss_window_new(&window, NULL, 0, 0, 0, WINDOW_W, WINDOW_H);

      strcpy(message, "SolarHunter");
      kiss_label_new(
          &label, &window, message,
          (window.rect.w / 2) - strlen(message) * kiss_textfont.advance / 2,
          (window.rect.h / 3)
      );
      label.textcolor.r = 255;
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
    void Cleanup() {
      kiss_clean(&objects);
      std::cout << "initialMenu cleanup" << std::endl;
    };

    void Pause() {};
    void Resume() {};

    void HandleEvents(Engine::State::CStateEngine* game) {
      kiss_window_event(&window, &game -> event, &draw);
      button_ini_event(&button_ini, &game -> event, &draw);
      button_exit_event(&button_exit, &game -> event, &draw, game);
    };

    void Draw(Engine::State::CStateEngine* game) {
      if (draw) {
        Crunch::Graphics.Clear();
        // kiss_window_draw(&window, Crunch::Graphics.renderer);
        kiss_label_draw(&label, Crunch::Graphics.renderer);
        kiss_button_draw(&button_ini, Crunch::Graphics.renderer);
        kiss_button_draw(&button_exit, Crunch::Graphics.renderer);
        draw = 0;
        Crunch::Graphics.Present();
      }
    };

    void Update(Engine::State::CStateEngine *game) {}

    static InitialMenuScene* Instance() {
      return &m_initialmenuscene;
    }

  protected:
    InitialMenuScene() {}

  private:
    static InitialMenuScene m_initialmenuscene;
    kiss_array objects;
    kiss_window window;
    kiss_label label = {0};
    kiss_button button_ini = {0}, button_exit = {0};
    char message[KISS_MAX_LENGTH];
    int draw = 1;
};
InitialMenuScene InitialMenuScene::m_initialmenuscene;

#endif
