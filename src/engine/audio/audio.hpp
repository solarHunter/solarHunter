#ifndef H_ENGINE_SOUND
#define H_ENGINE_SOUND
  #include "../sdl.h"

  namespace Engine {
    namespace Audio {
      class CAudio {
        public:
          CAudio();
          ~CAudio();

          void StopBacktrack();
          int LoadBacktrack(const char *path);
        private:
          Mix_Music *backtrack = nullptr;
      };
    }
  }

#endif
