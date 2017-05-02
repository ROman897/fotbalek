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
#include "../Components/UI/Button.h"
#include "../Components/Graphic/Sprite.h"
#include "../Components/Graphic/Label.h"
#include "../Components/Transform.h"
#include "../SettingsDefines.h"

template <typename TSettings>
class InputSystem{
    ComponentManager<TSettings>* m_manager;


    bool escape;
    float time = 0;

public:
    void run(float dt) {
        time += dt;
        if (time < GameConstants::kKeyCooldown)
            return;
        time -= GameConstants::kKeyCooldown;
        SDL_Event event;
        bool moveLeft = false;
        bool moveRight = false;
        bool moveUp = false;
        bool moveDown = false;
        bool shoot = false;
        int menuMoveUp = 0;
        int menuMoveDown = 0;


        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT){
                m_manager->setQuit(true);
            }


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
                    std::cout << "key up pressed " << std::endl;
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
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    escPressed();
                    continue;
                }

                if (escape) {

                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_UP:
                            m_manager->template forEntityMatching<SystemSignature_Button>(activeButtonId,
                                                                               [this](Button *button, Sprite *sprite,
                                                                                      Label *label,
                                                                                      const Transform *transform) {
                                                                                   button->isSelected = false;
                                                                                   this->activeButtonId = m_manager->findGameObjectByTag(
                                                                                           button->m_moveUpButtonTag);
                                                                                   m_manager->template forEntityMatching<SystemSignature_Sprite>(
                                                                                           activeButtonArrowId,
                                                                                           [&transform](Sprite *sprite,
                                                                                                        Transform *transform1) {
                                                                                               transform1->m_position =
                                                                                                       transform->m_position +
                                                                                                       GameConstants::kButtonOffset;
                                                                                           });
                                                                               });
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            m_manager->template forEntityMatching<SystemSignature_Button>(activeButtonId,
                                                                               [this](Button *button, Sprite *sprite,
                                                                                      Label *label,
                                                                                      const Transform *transform) {
                                                                                   button->isSelected = false;
                                                                                   this->activeButtonId = m_manager->findGameObjectByTag(
                                                                                           button->m_moveDownButtonTag);
                                                                                   m_manager->template forEntityMatching<SystemSignature_Sprite>(
                                                                                           activeButtonArrowId,
                                                                                           [&transform](Sprite *sprite,
                                                                                                        Transform *transform1) {
                                                                                               transform1->m_position =
                                                                                                       transform->m_position +
                                                                                                       GameConstants::kButtonOffset;
                                                                                           });
                                                                               });
                            break;

                        case SDLK_KP_ENTER:
                            m_manager->template forEntityMatching<SystemSignature_Button>(activeButtonId,
                                                                               [this](Button *button, Sprite *sprite,
                                                                                      Label *label, Transform* transform) {
                                                                                   button->isSelected = false;
                                                                                   for (auto &func : button->m_callbacks) {
                                                                                       func();
                                                                                   }
                                                                               });
                            escPressed();
                            break;
                        default:
                            break;
                    }

                }
            }
        }

            bool moveVertical = (moveUp && !moveDown) || (moveDown && !moveUp);
            bool moveHorizontal = (moveRight && !moveLeft) || (moveLeft && !moveRight);

            if (moveHorizontal || moveVertical || shoot) {
                m_manager->template forEntityMatching<SystemSignature_Input >(movementInputId,
                                           [moveHorizontal, moveVertical, moveUp, moveRight, shoot](MovementInputHolder *inputHolder) {
                                               inputHolder->moveUp = moveUp;
                                               inputHolder->moveRight = moveRight;
                                               inputHolder->moveVertical = moveVertical;
                                               inputHolder->moveHorizontal = moveHorizontal;
                                               inputHolder->shoot = shoot;
                                               inputHolder->valid = true;
                                           });
            }



    }

    void initialize(){
        activeButtonArrowId = m_manager->findGameObjectByTag("button_arrow");
        movementInputId = m_manager->template findEntityMatching<SystemSignature_Input>();
        escape = false;
        // now we need to decide how the button that is selected at the start is marked
    }

    void setManager(ComponentManager<settings >* manager){
        m_manager = manager;
    }

    void start(){

    }

private:
    Timer inputTimer;
// id of gameobject with movementinputholder component
    Id movementInputId;
    Id menuInputId;
    Id activeButtonId;
    Id activeButtonArrowId;

    void escPressed(){
        std::cout << "esc: " << escape << std::endl;
        escape = !escape;
        m_manager->template forEntitiesMatching<SystemSignature_Button>(
                [this](const Button *button, Sprite *sprite, Label *label, Transform* transform) {
                    sprite->enabled = escape;
                    label->enabled = escape;
                });
        /*m_manager->template forEntityMatching<SystemSignature_Sprite>(activeButtonArrowId, [this](Sprite *sprite,
                                                                                         const Transform *transform) {
            sprite->enabled = escape;
        });*/
    }


};

#endif //PV264_PROJECT_INPUTMANAGER_H
