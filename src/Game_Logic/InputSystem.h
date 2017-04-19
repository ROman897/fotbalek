//
// Created by roman on 19.4.2017.
//

#ifndef PV264_PROJECT_INPUTMANAGER_H
#define PV264_PROJECT_INPUTMANAGER_H

#include <SDL_events.h>
#include "../Components/InputHolder.h"
#include "../Utils/declarations.h"
#include "../Core/ComponentManager.h"

template <template typename TSettings>
class InputSystem{
    ComponentManager<TSettings>* manager;
    using SystemSignature_Input = Signature<InputHolder>;
    void handleInputs() {

        // implementation right now only forwards input to one component, after that PollEvent is empty
        manager->forEntitiesMatching<SystemSignature_Input>([](InputHolder& holder){
            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                // if event was SDL_QUIT we quit the main loop
                holder.events.emplace_back(std::move(event));
            }
        });


    }
};

#endif //PV264_PROJECT_INPUTMANAGER_H
