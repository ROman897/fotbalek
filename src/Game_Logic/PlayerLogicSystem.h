//
// Created by roman on 19.4.2017.
//

#ifndef PV264_PROJECT_INPUTMANAGER_H
#define PV264_PROJECT_INPUTMANAGER_H

#include <SDL_events.h>
#include "../Components/Logic/MovementInputHolder.h"
#include "../Utils/declarations.h"
#include "../Core/ComponentManager.h"
#include "../Constants/GameConstants.h"
#include "../Utils/Timer.h"
#include "../Components/UI/Button.h"
#include "../Components/Graphic/Sprite.h"
#include "../Components/Graphic/Label.h"
#include "../Components/Transform.h"
#include "../SettingsDefines.h"

template <typename TSettings>
class PlayerLogicSystem{
    ComponentManager<TSettings>* m_manager;


    bool m_escape;
    float time = 0;
    int m_Team1Score;
    int m_Team2Score;
    Id m_StateChangeId;
    Id m_ScoreLabel1Id;
    Id m_ScoreLabel2Id;
    Id m_GameOverLabelId;

public:
    void run(float dt) {
        time += dt;
        if (time < ClientGameConstants::kKeyCooldown)
            return;
        time -= ClientGameConstants::kKeyCooldown;
        SDL_Event event;
        bool moveLeft = false;
        bool moveRight = false;
        bool moveUp = false;
        bool moveDown = false;
        bool shoot = false;
        //int menuMoveUp = 0;
        //int menuMoveDown = 0;


        while (SDL_PollEvent(&event) != 0) {
            moveLeft = false;
            moveRight = false;
            moveUp = false;
            moveDown = false;
            shoot = false;
            if (event.type == SDL_QUIT){
                m_manager->setQuit(true);
            }


            if (event.type == SDL_KEYDOWN && !m_escape) {

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

                if (m_escape) {

                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_UP:
                            m_manager->template forEntityMatching_S<SystemSignature_Button>(activeButtonId,
                                                                               [this](Button *button, Sprite *sprite,
                                                                                      Label *label,
                                                                                      const Transform *transform) {
                                                                                   this->activeButtonId = m_manager->findGameObjectByTag(
                                                                                           button->m_moveUpButtonTag);

                                                                               });
                            setArrowPosition();
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            m_manager->template forEntityMatching_S<SystemSignature_Button>(activeButtonId,
                                                                               [this](Button *button, Sprite *sprite,
                                                                                      Label *label,
                                                                                      const Transform *transform) {
                                                                                   this->activeButtonId = m_manager->findGameObjectByTag(
                                                                                           button->m_moveDownButtonTag);
                                                                               });
                            setArrowPosition();
                            break;

                        case SDLK_RETURN:
                        if(activeButtonId == m_QuitButtonId){
                            m_manager->setQuit(true);
                        }
                            escPressed();
                            break;
                        default:
                            break;
                    }

                }
            }
        }

            bool moveVertical = (moveUp  || moveDown);
            bool moveHorizontal = (moveRight || moveLeft);

            if (moveHorizontal || moveVertical || shoot) {
                m_manager->template forEntityMatching_S<SystemSignature_Input >(movementInputId,
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

    void setManager(ComponentManager<settings >* manager){
        m_manager = manager;
    }

    void setActiveButton(Id id){
        activeButtonId = id;
    }

    void start(){
        activeButtonArrowId = m_manager->findGameObjectByTag("arrow");
        movementInputId = m_manager->template findEntityMatching<SystemSignature_Input>();
        m_escape = false;
        menuPanelId = m_manager->findGameObjectByTag("menuPanel");

        m_continueButtonId = m_manager->findGameObjectByTag(ClientGameConstants::kContinueButtonTag);
        m_OptionsButtonId = m_manager->findGameObjectByTag(ClientGameConstants::kOptionsButtonTag);
        m_QuitButtonId = m_manager->findGameObjectByTag(ClientGameConstants::kQuitButtonTag);
        Transform t;

        setArrowPosition();

    }

private:
    void updateState(){
        std::lock_guard<std::mutex> lock(m_manager->componentsMutex);
        m_manager->template forEntityMatching_S<SystemSignature_GameStateChange>(m_StateChangeId, [this](GameStateChange* stateChange){
            if (stateChange->m_Team1Scored) {
                team1Scored();
                stateChange->m_Team1Scored = false;
                return;
            }
            if (stateChange->m_Team2Scored){
                team2Scored();
                stateChange->m_Team2Scored = false;
                return;
            }
            if (stateChange->m_GameOver){
                gameOver();
                stateChange->m_GameOver = false;
                return;
            }

        });
    }
    void team1Scored(){
        ++m_Team1Score;
        m_manager->template forEntityMatching<SystemSignature_Label>(m_ScoreLabel1Id, [this](Label* label){

        });
    }

    void team2Scored(){
        ++m_Team2Score;
        m_manager->template forEntityMatching<SystemSignature_Label>(m_ScoreLabel2Id, [this](Label* label){

        });
    }

    void gameOver(){
        m_manager->template forEntityMatching<SystemSignature_Label>(m_GameOverLabelId, [this](Label* label){

        });
    }



    Timer inputTimer;
// id of gameobject with movementinputholder component
    Id movementInputId;
    Id activeButtonId;
    Id activeButtonArrowId;
    Id menuPanelId;
    Id m_continueButtonId;
    Id m_OptionsButtonId;
    Id m_QuitButtonId;

    void setArrowPosition(){

        std::lock_guard<std::mutex> lock(m_manager->componentsMutex);
        Transform t;
        m_manager->template forEntityMatching<SystemSignature_Button>(activeButtonId,
                                                                      [&t](Button *button, Sprite *sprite,
                                                                           Label *label,
                                                                           const Transform *transform) {
                                                                          t = *transform;
                                                                      });

        m_manager->template forEntityMatching<SystemSignature_SpriteGraphic>(
                activeButtonArrowId,
                [&t](Sprite *sprite,
                            Transform *transform1) {
                    transform1->m_position =
                            t.m_position +
                            ClientGameConstants::kButtonOffset;
                });
    }

    void escPressed(){
        std::lock_guard<std::mutex> lock(m_manager->componentsMutex);
        m_escape = !m_escape;
        m_manager->template forEntitiesMatching<SystemSignature_Button>(
                [this](const Button *button, Sprite *sprite, Label *label, Transform* transform) {
                    sprite->m_enabled = m_escape;
                    label->m_Enabled = m_escape;
                });
        m_manager->template forEntityMatching<SystemSignature_RectangleGraphic>(menuPanelId, [this](RectangleShape* rect, Transform* trans){
            rect->m_enabled = m_escape;
        });
        m_manager->template forEntityMatching<SystemSignature_SpriteGraphic >(activeButtonArrowId, [this](Sprite *sprite,
                                                                                         const Transform *transform) {
            sprite->m_enabled = m_escape;
        });
    }


};

#endif //PV264_PROJECT_INPUTMANAGER_H