//
// Created by roman on 19.4.2017.
//

#ifndef PV264_PROJECT_INPUTMANAGER_H
#define PV264_PROJECT_INPUTMANAGER_H

#include "../Components/Graphic/Label.h"
#include "../Components/Graphic/Sprite.h"
#include "../Components/Logic/MovementInputHolder.h"
#include "../Components/Transform.h"
#include "../Components/UI/Button.h"
#include "../Constants/GameConstants.h"
#include "../Core/ComponentManager.h"
#include "../SettingsDefines.h"
#include "../Utils/Declarations.h"
#include "../Utils/Timer.h"
#include <SDL_events.h>

template <typename TSettings> class PlayerLogicSystem {
  ComponentManager<TSettings> *m_manager;

  bool m_escape;
  float m_time = 0;
  int m_Team1Score;
  int m_Team2Score;
  Id m_StateChangeId;
  Id m_ScoreLabel1Id;
  Id m_ScoreLabel2Id;
  Id m_GameOverLabelId;

  Id m_Team1ScoredLabelId;
  Id m_Team2ScoredLabelId;

  Id m_ActiveLabelId;
  bool m_labelActive;
  float m_labelTime;

  Timer inputTimer;
  // id of gameobject with movementinputholder component
  Id movementInputId;
  Id activeButtonId;
  Id activeButtonArrowId;
  Id menuPanelId;
  Id m_continueButtonId;
  Id m_OptionsButtonId;
  Id m_QuitButtonId;

  bool moveLeft = false;
  bool moveRight = false;
  bool moveUp = false;
  bool moveDown = false;
  bool shoot = false;

public:
  void run(float dt) {
    if (m_labelActive) {
      m_labelTime += dt;
      if (m_labelTime > ClientGameConstants::kLabelHideTime)
        resetActiveLabel();
    }

    m_time += dt;
    if (m_time < ClientGameConstants::kKeyCooldown)
      return;

    std::lock_guard<std::mutex> lock(m_manager->componentsMutex);
    updateState();
    m_time -= ClientGameConstants::kKeyCooldown;
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
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
            m_manager->template forEntityMatching<SystemSignature_Button>(
                activeButtonId,
                [this](Button *button, Sprite *sprite, Label *label,
                       const Transform *transform) {
                  this->activeButtonId =
                      m_manager->findGameObjectByTag(button->m_moveUpButtonTag);

                });
            setArrowPosition();
            break;
          case SDLK_s:
          case SDLK_DOWN:
            m_manager->template forEntityMatching<SystemSignature_Button>(
                activeButtonId,
                [this](Button *button, Sprite *sprite, Label *label,
                       const Transform *transform) {
                  this->activeButtonId = m_manager->findGameObjectByTag(
                      button->m_moveDownButtonTag);
                });
            setArrowPosition();
            break;

          case SDLK_RETURN:
            if (activeButtonId == m_QuitButtonId) {
              m_manager->setQuit(true);
            }
            escPressed();
            break;
          default:
            break;
          }

        } else {

          switch (event.key.keysym.sym) {
          case SDLK_a:
          case SDLK_LEFT:
            moveLeft = false;
            break;
          case SDLK_d:
          case SDLK_RIGHT:
            moveRight = false;
            break;
          case SDLK_w:
          case SDLK_UP:
            moveUp = false;
            break;
          case SDLK_s:
          case SDLK_DOWN:
            moveDown = false;
            break;
          default:
            break;
          }
        }
      }
    }

    bool moveVertical = (moveUp || moveDown);
    bool moveHorizontal = (moveRight || moveLeft);

    if (moveHorizontal || moveVertical || shoot) {
      m_manager->template forEntityMatching<SystemSignature_Input>(
          movementInputId, [moveHorizontal, moveVertical,
                            this](MovementInputHolder *inputHolder) {
            inputHolder->moveUp = moveUp;
            inputHolder->moveRight = moveRight;
            inputHolder->moveVertical =
                moveVertical || inputHolder->moveVertical;
            inputHolder->moveHorizontal =
                moveHorizontal || inputHolder->moveHorizontal;
            inputHolder->shoot = shoot;
            inputHolder->valid = true;
          });
    }
  }

  void setManager(ComponentManager<settings> *manager) { m_manager = manager; }

  void setActiveButton(Id id) { activeButtonId = id; }

  void start() {
    activeButtonArrowId = m_manager->findGameObjectByTag("arrow");
    movementInputId =
        m_manager->template findEntityMatching<SystemSignature_Input>();
    m_escape = false;
    menuPanelId = m_manager->findGameObjectByTag("menuPanel");

    m_continueButtonId =
        m_manager->findGameObjectByTag(ClientGameConstants::kContinueButtonTag);
    m_OptionsButtonId =
        m_manager->findGameObjectByTag(ClientGameConstants::kOptionsButtonTag);
    m_QuitButtonId =
        m_manager->findGameObjectByTag(ClientGameConstants::kQuitButtonTag);

    m_GameOverLabelId =
        m_manager->findGameObjectByTag(ClientGameConstants::kGameoverLabelTag);
    m_Team1ScoredLabelId =
        m_manager->findGameObjectByTag(ClientGameConstants::kScored1LabelTag);
    m_Team2ScoredLabelId =
        m_manager->findGameObjectByTag(ClientGameConstants::kScored2LabelTag);

    m_StateChangeId =
        m_manager
            ->template findEntityMatching<SystemSignature_GameStateChange>();

    setArrowPosition();
  }

  PlayerLogicSystem()
      : m_Team1Score(0), m_Team2Score(0), m_labelActive(false),
        m_labelTime(false) {}

private:
  void updateState() {
    m_manager->template forEntityMatching<SystemSignature_GameStateChange>(
        m_StateChangeId, [this](GameStateChange *stateChange) {
          if (stateChange->m_Team1Scored) {
            std::cout << "team 1 scored" << std::endl;
            team1Scored();
            stateChange->m_Team1Scored = false;
            return;
          }
          if (stateChange->m_Team2Scored) {
            std::cout << "team 2 scored" << std::endl;
            team2Scored();
            stateChange->m_Team2Scored = false;
            return;
          }
          if (stateChange->m_GameOver) {
            gameOver();
            stateChange->m_GameOver = false;
            return;
          }

        });
  }
  void team1Scored() {
    resetActiveLabel();
    ++m_Team1Score;
    m_manager->template forEntityMatching<SystemSignature_Label>(
        m_ScoreLabel1Id, [this](Label *label) {

        });

    m_labelActive = true;
    m_ActiveLabelId = m_Team1ScoredLabelId;

    m_manager->template forEntityMatching<SystemSignature_Label>(
        m_Team1ScoredLabelId,
        [this](Label *label) { label->m_Enabled = true; });
  }

  void team2Scored() {
    resetActiveLabel();
    ++m_Team2Score;
    m_manager->template forEntityMatching<SystemSignature_Label>(
        m_ScoreLabel2Id, [this](Label *label) {

        });

    m_labelActive = true;
    m_ActiveLabelId = m_Team2ScoredLabelId;

    m_manager->template forEntityMatching<SystemSignature_Label>(
        m_Team2ScoredLabelId,
        [this](Label *label) { label->m_Enabled = true; });
  }

  void gameOver() {
    resetActiveLabel();

    m_labelActive = true;
    m_ActiveLabelId = m_GameOverLabelId;
    m_manager->template forEntityMatching<SystemSignature_Label>(
        m_GameOverLabelId, [this](Label *label) { label->m_Enabled = true; });
  }

  void resetActiveLabel() {
    m_labelTime = 0;
    m_manager->template forEntityMatching<SystemSignature_Label>(
        m_ActiveLabelId, [this](Label *label) { label->m_Enabled = false; });
    m_labelActive = false;
  }

  void setArrowPosition() {
    Transform t;
    m_manager->template forEntityMatching<SystemSignature_Button>(
        activeButtonId, [&t](Button *button, Sprite *sprite, Label *label,
                             const Transform *transform) { t = *transform; });

    m_manager->template forEntityMatching<SystemSignature_SpriteGraphic>(
        activeButtonArrowId, [&t](Sprite *sprite, Transform *transform1) {
          transform1->m_position =
              t.m_position + ClientGameConstants::kButtonOffset;
        });
  }

  void escPressed() {
    m_escape = !m_escape;
    m_manager->template forEntitiesMatching<SystemSignature_Button>(
        [this](const Button *button, Sprite *sprite, Label *label,
               Transform *transform) {
          sprite->m_enabled = m_escape;
          label->m_Enabled = m_escape;
        });
    m_manager->template forEntityMatching<SystemSignature_RectangleGraphic>(
        menuPanelId, [this](RectangleShape *rect, Transform *trans) {
          rect->m_enabled = m_escape;
        });
    m_manager->template forEntityMatching<SystemSignature_SpriteGraphic>(
        activeButtonArrowId,
        [this](Sprite *sprite, const Transform *transform) {
          sprite->m_enabled = m_escape;
        });
  }
};

#endif // PV264_PROJECT_INPUTMANAGER_H
