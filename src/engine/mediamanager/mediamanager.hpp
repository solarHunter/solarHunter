#ifndef H_ENGINE_MEDIAMANAGER
#define H_ENGINE_MEDIAMANAGER
  #include "../sdl.h"

  #include <iostream>
  #include <thread>
  #include <string>
  #include <map>

  namespace Engine {
    namespace Media {

      typedef std::map<const char*, const char*> MediaList;
      typedef MediaList::iterator MediaList_iterator;
      typedef std::map<const char*, SDL_Surface*> ImageList;
      typedef ImageList::iterator ImageList_iterator;

      typedef struct {
        MediaList *list, *audio;
        ImageList *images;
        int *loaded;
        int *error;
      } MediaData;

      class CMedia {
        public:
          ~CMedia();
          CMedia();
          int Load(MediaList *list, void (update)(const int, const int));
          ImageList images;
          MediaList audio;

        private:
          int loaded, tot_loaded;
      };
    }
  }

#endif
