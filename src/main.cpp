#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "utils.h"

int main() {
  srand(time(NULL));
  std::cout << "testing " << utils::randI32(0, 10) << std::endl;
}
