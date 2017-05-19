#include "mediamanager.hpp"
#include <stdlib.h>

void* res_load(void *d) {
  Engine::Media::MediaData *data = (Engine::Media::MediaData*)d;
  std::string path, ext;
  SDL_Surface *surface;
  for(Engine::Media::MediaList_iterator i = (*data -> list).begin(); i != (*data -> list).end(); ++i) {
    if ((*data -> images).count(i -> first) + (*data -> audio).count(i -> first) == 0) {
      path = i -> second;
      ext = path.substr(path.length() - 4);

      if (ext == ".png" ||
          ext == ".jpg" ||
          ext == "jpeg") {

        surface = IMG_Load(i -> second);
        if (!surface || surface == NULL){
          std::cout << "ERROR::IMG_Load: " << SDL_GetError() << std::endl;
          SDL_FreeSurface(surface);
          (*data -> error) = 1;
        } else {
          (*data -> images)[i -> first] = surface;
          std::cout << "loaded " << i -> first << std::endl;
        }

      } else if (ext == ".mp3" ||
          ext == ".mp4" ||
          ext == ".wov" ||
          ext == "mpeg") {
        (*data -> audio)[i -> first] = i -> second;
      }
    }

    (*data -> loaded)++;
  }
}

Engine::Media::CMedia::CMedia() {
  std::cout << "Init::Media" << std::endl;
}

Engine::Media::CMedia::~CMedia() {
  for(Engine::Media::ImageList_iterator i = images.begin(); i != images.end(); ++i) {
    SDL_FreeSurface(i -> second);
    std::cout << "Media free: " << i -> first << std::endl;
  }
}

int Engine::Media::CMedia::Load(Engine::Media::MediaList *list, void (update)(const int, const int)) {
  int error = 0;
  this -> tot_loaded = list -> size();
  this -> loaded = 0;

  Engine::Media::MediaData *data = (Engine::Media::MediaData*)malloc(sizeof(Engine::Media::MediaData));
  data -> list = list,
  data -> images = &images,
  data -> audio = &audio,
  data -> loaded = &loaded;
  data -> error = &error;

  pthread_t th_load;
  pthread_create(&th_load, NULL, res_load, (void*)data);

  while (this -> loaded < tot_loaded) {
    if (update != NULL) update(this -> loaded, this -> tot_loaded);
  }

  pthread_join(th_load, NULL);
  free(data);

  return error;
}
