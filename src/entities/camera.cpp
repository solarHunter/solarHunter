#include "camera.hpp"

CCamera::CCamera() {
  w = Crunch.screen_width;
  h = Crunch.screen_height;
  roomSize = Crunch.screen_height * 2.5;
}

CCamera::~CCamera() {}

void CCamera::setCamera(int posX, int posY)
{
    x = posX - Crunch.screen_width;
    y = posY - Crunch.screen_height;
    
    if(x < 0) x = 0;    
    if(y < 0) y = 0;
    if(x > roomSize) x = roomSize - w;    
    if(y > roomSize) y = roomSize - h;    
}