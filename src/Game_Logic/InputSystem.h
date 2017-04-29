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
        bool moveLeft = false;
        bool moveRight = false;
        bool moveUp = false;
        bool moveDown = false;
        bool shoot = false;
        bool escape = false;
        int menuMoveUp = 0;
        int menuMoveDown = 0;


        while (SDL_PollEvent(&event) != 0) {


                if (event.type == SDL_KEYDOWN && !escape) {

                    switch (event.key.keysym.sym) {
                        case SDLK_a:
                        case SDLK_LEFT:
                            moveLeft = true;
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            moveRight = true;
                            break;
                        case SDLK_w:
                        case SDLK_UP:
                            moveUp = true;
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            moveDown = true;
                            break;
                        default:
                            break;
                    }
                }



            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        escape = true;
                    case SDLK_w:
                    case SDLK_UP:
                        moveUp = true;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        moveDown = true;
                        break;

                    default:
                        break;
                }

            }

            bool moveVertical = (moveUp && !moveDown) || (moveDown && !moveUp);
            bool moveHorizontal = (moveRight && !moveLeft) || (moveLeft && !moveRight);

            if (moveHorizontal || moveVertical || shoot) {
                manager->forEntityMatching(movementInputId,
                                           [moveHorizontal, moveVertical, moveUp, moveDown, shoot](auto &inputHolder) {
                                               inputHolder.moveUp = moveUp;
                                               inputHolder.moveRight = moveRight;
                                               inputHolder.moveVertical = moveVertical;
                                               inputHolder.moveHorizontal = moveHorizontal;
                                               inputHolder.shoot = shoot;
                                               inputHolder.valid = true;
                                           });
            }


        }
    }

private:
Timer inputTimer;
// id of gameobject with movementinputholder component
Id movementInputId;
Id menuInputId;

};

#endif //PV264_PROJECT_INPUTMANAGER_H
