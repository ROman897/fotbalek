//
// Created by roman on 19.4.2017.
//

#ifndef PV264_PROJECT_INPUTMANAGER_H
#define PV264_PROJECT_INPUTMANAGER_H

#include <SDL_events.h>
#include "../Components/MovementInputHolder.h"
#include "../Utils/declarations.h"
#include "../Core/ComponentManager.h"
#include "../Utils/GameConstants.h"
#include "../Utils/Timer.h"

template <template typename TSettings>
class InputSystem{
    ComponentManager<TSettings>* manager;
    using SystemSignature_Input = Signature<MovementInputHolder>;
    void handleInputs() {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {

            if (event.type == SDL_KEYDOWN && inputTimer.getTime() >= GameConstants::kInputCooldown) {
                // key was pressed down and it can react to input
                inputTimer.resetTime();
                //Adjust the velocity
                // do action based on key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                }
            }
        }

        // implementation right now only forwards input to one component, after that PollEvent is empty
        manager->forEntitiesMatching<SystemSignature_Input>([](MovementInputHolder& holder){
            SDL_Event event;

                // if event was SDL_QUIT we quit the main loop
                if (event == SDL_Event)
            }
        });


    }

private:
Timer inputTimer;

};

#endif //PV264_PROJECT_INPUTMANAGER_H
