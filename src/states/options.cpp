#include "../engine/engine.hpp"

#include "options.hpp"

OptionsScene OptionsScene::m_optionsscene;

void OptionsScene::button_exit_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine* state) {
  if (kiss_button_event(button, e, draw)) {
    state -> PopState();
  }
}

void OptionsScene::button_video_event(kiss_button *button, SDL_Event *e, int *draw) {
  if (kiss_button_event(button, e, draw)) {
    main_window.visible = 0;
    video_window.visible = 1;
  }
}

void OptionsScene::combo_resolution_event(kiss_combobox *combo, SDL_Event *e, int *draw) {
  if (kiss_combobox_event(combo, e, draw)) {}
}

void OptionsScene::select_fullscreen_event(kiss_selectbutton *select, SDL_Event *e, int *draw) {
  if (kiss_selectbutton_event(select, e, draw)) {}
}

void OptionsScene::select_vsync_event(kiss_selectbutton *select, SDL_Event *e, int *draw) {
  if (kiss_selectbutton_event(select, e, draw)) {}
}

void OptionsScene::button_video_save_event(kiss_button *button, SDL_Event *e, int *draw) {
  if (kiss_button_event(button, e, draw)) {
    int index = video_resolutions.textbox.firstline + video_resolutions.textbox.selectedline;
    if (index >= 0) {
      Crunch.Configuration.Options["resolution_x"] = std::to_string(sresolutions[index].x);
      Crunch.Configuration.Options["resolution_y"] = std::to_string(sresolutions[index].y);
      needRestart = 1;
    }
    std::string parsed_vsync = std::to_string(video_vsync_select.selected);
    if (parsed_vsync != Crunch.Configuration.Options["vsync"]) {
      Crunch.Configuration.Options["vsync"] = parsed_vsync;
      needRestart = 1;
    }
    std::string parsed_fullscreen = std::to_string(video_fullscreen_select.selected);
    if (parsed_fullscreen != Crunch.Configuration.Options["fullscreen"]) {
      Crunch.Configuration.Options["fullscreen"] = parsed_fullscreen;
      Crunch.Graphics.setFullscreen(video_fullscreen_select.selected);
    }
    Crunch.Configuration.Save(Crunch.Configuration.options_path, Crunch.Configuration.Options);
    if (needRestart) {
      main_window.visible = 0;
      video_window.visible = 0;
      needRestart_window.visible = 1;
    }
  }
}

void OptionsScene::button_back_event(kiss_button *button, SDL_Event *e, int *draw) {
  if (kiss_button_event(button, e, draw)) {
    main_window.visible = 1;
    video_window.visible = 0;
  }
}

void OptionsScene::button_restart_event(kiss_button *button, SDL_Event *e, int *draw, Engine::State::CStateEngine *state) {
  if (kiss_button_event(button, e, draw)) {
    state -> Quit();
  }
}

void OptionsScene::Init() {
  background = Crunch.Graphics.Textures.Load("./media/background.jpg");

  // Main window
  kiss_window_new(
      &main_window, NULL, 0, 0, 0,
      atoi(Crunch.Configuration.Options["resolution_x"].c_str()),
      atoi(Crunch.Configuration.Options["resolution_y"].c_str())
      );

  kiss_label_new(
      &main_label, &main_window, main_title,
      (main_window.rect.w / 2) - strlen(main_title) * kiss_textfont.advance / 2,
      (main_window.rect.h / 3)
      );
  main_label.textcolor.r = 255;
  main_label.textcolor.g = 255;
  main_label.textcolor.b = 255;

  kiss_button_new(
      &button_video, &main_window, (char*)"VIDEO",
      main_window.rect.w / 2 - kiss_normal.w / 2,
      main_label.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );

  kiss_button_new(
      &button_exit, &main_window, (char*)"EXIT",
      main_window.rect.w / 2 - kiss_normal.w / 2,
      button_video.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );
  main_window.visible = 1;


  // Video window
  kiss_window_new(
      &video_window, NULL, 0, 0, 0,
      atoi(Crunch.Configuration.Options["resolution_x"].c_str()),
      atoi(Crunch.Configuration.Options["resolution_y"].c_str())
      );

  kiss_label_new(
      &video_label, &video_window, video_title,
      (video_window.rect.w / 2) - strlen(video_title) * kiss_textfont.advance / 2,
      (video_window.rect.h / 3)
      );
  video_label.textcolor.r = 255;
  video_label.textcolor.g = 255;
  video_label.textcolor.b = 255;

  kiss_array_new(&resolutions);
  for (int i = 0; i < resolutionsc; i++)
    kiss_array_appendstring(&resolutions, 0, sresolutions[i].name, NULL);


  int combobox_width = 150;
  int combobox_height = 96;
  int off = (combobox_width + kiss_up.w - kiss_edge);

  char *res_ini = (char*)(Crunch.Configuration.Options["resolution_x"] + "x" + Crunch.Configuration.Options["resolution_y"]).c_str();
  kiss_combobox_new(&video_resolutions, &video_window,
      res_ini,
      &resolutions,
      // video_label.rect.x - kiss_edge,
      (video_window.rect.w / 2) - strlen(video_title) * kiss_textfont.advance / 2 - off / 3,
      video_label.rect.y + kiss_textfont.fontheight + kiss_normal.h,
      combobox_width, combobox_height);

  // TOGGLE FULLSCREEN
  kiss_label_new(
      &video_fullscreen_label, &video_window, (char*)"Fullscreen",
      (video_window.rect.w / 2) - strlen(video_title) * kiss_textfont.advance / 2 - off / 3,
      video_resolutions.entry.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );
  video_fullscreen_label.textcolor.r = 255;
  video_fullscreen_label.textcolor.g = 255;
  video_fullscreen_label.textcolor.b = 255;

  kiss_selectbutton_new(&video_fullscreen_select, &video_window,
      video_fullscreen_label.rect.x + combobox_width + kiss_up.w - kiss_edge - kiss_selected.w,
      video_resolutions.entry.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );
  video_fullscreen_select.selected = atoi(Crunch.Configuration.Options["fullscreen"].c_str());
  // END TOGGLE FULLSCREEN

  // TOGGLE VSYNC
  kiss_label_new(
      &video_vsync_label, &video_window, (char*)"VSync",
      (video_window.rect.w / 2) - strlen(video_title) * kiss_textfont.advance / 2 - off / 3,
      video_fullscreen_label.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );
  video_vsync_label.textcolor.r = 255;
  video_vsync_label.textcolor.g = 255;
  video_vsync_label.textcolor.b = 255;

  kiss_selectbutton_new(&video_vsync_select, &video_window,
      video_vsync_label.rect.x + combobox_width + kiss_up.w - kiss_edge - kiss_selected.w,
      video_fullscreen_select.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );
  video_vsync_select.selected = atoi(Crunch.Configuration.Options["vsync"].c_str());
  // END TOGGLE VSYNC

  kiss_button_new(
      &button_video_save, &video_window, (char*)"SAVE",
      video_window.rect.w / 2 - kiss_normal.w / 2,
      video_vsync_label.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );

  kiss_button_new(
      &button_back, &video_window, (char*)"BACK",
      video_window.rect.w / 2 - kiss_normal.w / 2,
      button_video_save.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );
  video_window.visible = 0;


  // Restart needed window
  kiss_window_new(
      &needRestart_window, NULL, 0, 0, 0,
      atoi(Crunch.Configuration.Options["resolution_x"].c_str()),
      atoi(Crunch.Configuration.Options["resolution_y"].c_str())
      );

  kiss_label_new(
      &needRestart_label, &needRestart_window, needRestart_title,
      (needRestart_window.rect.w / 2) - strlen(needRestart_title) * kiss_textfont.advance / 2,
      (needRestart_window.rect.h / 3)
      );
  needRestart_label.textcolor.r = 255;
  needRestart_label.textcolor.g = 255;
  needRestart_label.textcolor.b = 255;

  kiss_button_new(
      &button_restart, &needRestart_window, (char*)"EXIT",
      needRestart_window.rect.w / 2 - kiss_normal.w / 2,
      needRestart_label.rect.y + kiss_textfont.fontheight + kiss_normal.h
      );
  needRestart_window.visible = 0;
};

void OptionsScene::HandleEvents(Engine::State::CStateEngine* state) {
  kiss_window_event(&main_window, &state -> event, &draw);
  button_video_event(&button_video, &state -> event, &draw);
  button_exit_event(&button_exit, &state -> event, &draw, state);

  kiss_window_event(&video_window, &state -> event, &draw);
  combo_resolution_event(&video_resolutions, &state -> event, &draw);
  select_fullscreen_event(&video_fullscreen_select, &state -> event, &draw);
  select_vsync_event(&video_vsync_select, &state -> event, &draw);
  button_video_save_event(&button_video_save, &state -> event, &draw);
  button_back_event(&button_back, &state -> event, &draw);

  kiss_window_event(&needRestart_window, &state -> event, &draw);
  button_restart_event(&button_restart, &state -> event, &draw, state);
};

void OptionsScene::Draw(Engine::State::CStateEngine* state) {
  if (draw) {
    Crunch.Graphics.Clear();
    // kiss_window_draw(&window, Crunch.Graphics.renderer);
    Crunch.Graphics.Textures.Draw(background, 0, 0, Crunch.screen_width, Crunch.screen_height);

      // MAIN
      kiss_label_draw(&main_label, Crunch.Graphics.renderer);
      kiss_button_draw(&button_video, Crunch.Graphics.renderer);
      kiss_button_draw(&button_exit, Crunch.Graphics.renderer);

      // VIDEO
      kiss_label_draw(&video_label, Crunch.Graphics.renderer);
      kiss_label_draw(&video_fullscreen_label, Crunch.Graphics.renderer);
      kiss_selectbutton_draw(&video_fullscreen_select, Crunch.Graphics.renderer);
      kiss_label_draw(&video_vsync_label, Crunch.Graphics.renderer);
      kiss_selectbutton_draw(&video_vsync_select, Crunch.Graphics.renderer);
      kiss_button_draw(&button_video_save, Crunch.Graphics.renderer);
      kiss_button_draw(&button_back, Crunch.Graphics.renderer);
      kiss_combobox_draw(&video_resolutions, Crunch.Graphics.renderer);

      // NEED RESTART
      kiss_label_draw(&needRestart_label, Crunch.Graphics.renderer);
      kiss_button_draw(&button_restart, Crunch.Graphics.renderer);

    draw = 0;

    Crunch.Graphics.Present();
  }
};
