#ifndef H_STATES_OPTIONS
#define H_STATES_OPTIONS
#include "../engine/engine.hpp"
#include <iostream>

class OptionsScene : public Engine::State::CState {
  public:
    void Init();
    void Cleanup() {};

    void Pause() {};
    void Resume() {};

    void HandleEvents(Engine::State::CStateEngine* state);
    void Draw(Engine::State::CStateEngine* state);
    void Update(Engine::State::CStateEngine *state) {};

    static OptionsScene* Instance() {
      return &m_optionsscene;
    }

  protected:
    OptionsScene() {}

  private:
    static OptionsScene m_optionsscene;
    int background;

    typedef struct {
      char name[12];
      int x;
      int y;
    } t_resolutions;
    t_resolutions sresolutions[8] {
      {"800x600\0", 800, 600},
      {"1024x768\0", 1024, 768},
      {"1024x800\0", 1024, 800},
      {"1280x720\0", 1280, 720},
      {"1280x768\0", 1280, 768},
      {"1280x900\0", 1280, 900},
      {"1440x900\0", 1440, 900},
      {"1920x1080\0", 1920, 1080}
    };
    int resolutionsc = 8;
    kiss_array resolutions;

    // Main
    kiss_window main_window;
    kiss_label main_label = {0};
    kiss_button button_exit = {0}, button_video = {0};
    char *main_title = (char*)"Options\0";

    // Video
    kiss_window video_window;
    kiss_label
      video_label = {0},
      video_fullscreen_label = {0},
      video_vsync_label = {0};

    kiss_button
      button_video_save = {0},
      button_back = {0};

    kiss_combobox video_resolutions = {0};

    kiss_selectbutton
      video_fullscreen_select = {0},
      video_vsync_select = {0};
    char *video_title = (char*)"Video";


    // need restart
    int needRestart = 0;
    kiss_window needRestart_window;
    kiss_label needRestart_label = {0};
    kiss_button button_restart = {0};
    char *needRestart_title = (char*)"Restart the game to apply the changes";

    int draw = 1;

    void button_video_event(kiss_button *button, SDL_Event *e, int *draw);
    void button_exit_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state);

    void combo_resolution_event(kiss_combobox *combo, SDL_Event *e, int *draw);
    void select_fullscreen_event(kiss_selectbutton *button, SDL_Event *e, int *draw);
    void select_vsync_event(kiss_selectbutton *button, SDL_Event *e, int *draw);
    void button_video_save_event(kiss_button *button, SDL_Event *e, int *draw);
    void button_back_event(kiss_button *button, SDL_Event *e, int *draw);

    void button_restart_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine *state);
};

#endif
