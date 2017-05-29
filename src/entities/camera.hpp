#ifndef H_ENTITY_CAMERA
#define H_ENTITY_CAMERA

#include "../engine/engine.hpp"

class CCamera {
  public:
    CCamera();
    ~CCamera();

    void setCamera(int posX, int posY);

    int x, y, w, h;

  private:
    int roomSize;
};

#endif
