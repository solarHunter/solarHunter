#include "utils.h"

int utils::randI32(const int min, const int max) {
  return rand() % (max - min) + min;
}
