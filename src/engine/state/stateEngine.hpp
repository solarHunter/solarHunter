#ifndef H_STATEMACHINE_ENGINE
#define H_STATEMACHINE_ENGINE

#include <vector>
#include "../sdl.h"

namespace Engine {
  namespace State {
    class CState;
    class CStateEngine {
      public:

        void Init();
        void Cleanup();

        void ChangeState(CState* state);
        void PushState(CState* state);
        void PopState();

        void HandleEvents();
        void Update();
        void Draw();

        bool Running() { return m_running; }
        void Quit() { m_running = false; }

        SDL_Event event;

      private:
        std::vector<CState*> states;
        bool m_running = true;
    };

    class CState {
      public:
        virtual void Init() = 0;
        virtual void Cleanup() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleEvents(CStateEngine* game) = 0;
        virtual void Update(CStateEngine* game) = 0;
        virtual void Draw(CStateEngine* game) = 0;

        void ChangeState(CStateEngine* game, CState* state) {
          game -> ChangeState(state);
        }

      protected:
        CState() {}
    };
  }
}

#endif
