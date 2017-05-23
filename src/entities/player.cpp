#include "player.hpp"

CPlayer::CPlayer() {
  sprite.image = Crunch.Graphics.Textures.Load("./media/spaceship.png");
  sprite.frame_width = 66;
  sprite.frame_height = 80;
  x = Crunch.screen_width/2;
  y = Crunch.screen_height/2;
  cameraW = Crunch.screen_width;
  cameraH = Crunch.screen_height;
}

CPlayer::~CPlayer() {}

void CPlayer::HandleEvents(Engine::State::CStateEngine* game) {
  dxRotation = game -> cursorX - x;
  dyRotation = game -> cursorY - y;
  facingAngle = atan2(dxRotation, -dyRotation) * 180 / PI;

  if (game -> event.type == SDL_KEYDOWN){
    switch (game -> event.key.keysym.scancode) {
      case 26:  KW = 1; break;
      case 7:   KD = 1; break;
      case 22:  KS = 1; break;
      case 4:   KA = 1; break;
      default: break;
    }
  } if (game -> event.type == SDL_KEYUP){
    switch (game -> event.key.keysym.scancode) {
      case 26:  KW = 0; break;
      case 7:   KD = 0; break;
      case 22:  KS = 0; break;
      case 4:   KA = 0; break;
      default: break;
    }
  }
}

void CPlayer::Update(Engine::State::CStateEngine* game) {
  if (KW) velocityY -= thrust;
  if (KD) velocityX += thrust;
  if (KS) velocityY += thrust;
  if (KA) velocityX -= thrust;

  if (velocityX < 0.1 && velocityX > -0.1) {
    velocityX = 0;
  } else {
    velocityX *= friction;
  }

  if (velocityY < 0.1 && velocityY > -0.1) {
    velocityY = 0;
  } else {
    velocityY *= friction;
  }

  if (velocityX > max_velocity) velocityX = max_velocity;
  if (velocityY > max_velocity) velocityY = max_velocity;
  if (velocityX < -max_velocity) velocityX = -max_velocity;
  if (velocityY < -max_velocity) velocityY = -max_velocity;

  if (velocityX > 0 && x + sprite.frame_width/2 < Crunch.screen_height * 2.5) {
    x += velocityX; 
  } else if (velocityX < 0 && x - sprite.frame_width/2 > 0) {
    x += velocityX;
  }

  if (velocityY > 0 && y + sprite.frame_height/2 < Crunch.screen_height * 2.5) {
    y += velocityY;
  } else if (velocityY < 0 && y - sprite.frame_height/2 > 0) {
    y += velocityY;
  }
}

void CPlayer::Draw() {
  Crunch.Graphics.Textures.Draw(
      sprite.image,
      x - sprite.frame_width / 2, y - sprite.frame_height / 2,
      sprite.frame_width, sprite.frame_height,
      facingAngle);
}

int CPlayer::getX() {
  return x;
}

int CPlayer::getY() {
  return y;
}

void CPlayer::setCamera()
{
    cameraX = (x + sprite.frame_width/2) - Crunch.screen_width;
    cameraY = (y + sprite.frame_height/2) - Crunch.screen_height;
    
    if(cameraX < 0) cameraX = 0;    
    if(cameraY < 0) cameraY = 0;
    if(cameraX > Crunch.screen_height*2.5 - cameraW) cameraX = Crunch.screen_height*2.5 - cameraW;    
    if(cameraY > Crunch.screen_height*2.5 - cameraH) cameraY = Crunch.screen_height*2.5 - cameraH;    

    x = x - cameraX;
    y = y - cameraY;
}