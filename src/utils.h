#ifndef H_UTILS
#define H_UTILS
#include <stdlib.h>

namespace utils {
  int randI32(const int, const int);

  int initializeSDL(SDL_Window**);
  void quitSDL(void);
}

#endif
