#ifndef H_ENTITY_PLAYER
#define H_ENTITY_PLAYER

#include "../engine/engine.hpp"

typedef struct {
  int image;
  int frame_width, frame_height;
} Sprite;

class CPlayer {
  public:
    CPlayer();
    ~CPlayer();

    void HandleEvents(Engine::State::CStateEngine* game);
    void Update(Engine::State::CStateEngine* game);
    void Draw();

  private:
    int x, y;
    Sprite sprite;

    float facingAngle;
    int dxRotation, dyRotation;

    char KW, KD, KS, KA;
    float friction = 0.98f, thrust = 0.6f, max_velocity = 6.0f;
    float velocityX = 0, velocityY = 0;
};

#endif
