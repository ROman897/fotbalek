//
// Created by roman on 3.5.2017.
//

#ifndef PV264_PROJECT_CLIENTGAMECONSTANTS_H
#define PV264_PROJECT_CLIENTGAMECONSTANTS_H

#include "../Utils/Declarations.h"
#include <SDL_pixels.h>
#include <string>

enum GraphicLayers { BACKGROUND, FOREGROUND, MISC, BACKUI, FRONTUI };

struct ClientGameConstants {
  //-------------------graphic layers
  constexpr static int kNumberOfLayers = 5;
  //-------------------//graphic layers

  //--------------------window
  constexpr static int kWindowHeight = 1000;
  constexpr static int kWindowWidth = 1200;
  //--------------------//window

  //------------------------Football pitch
  static const Vector_Float kPitchPos;
  static const Vector_Float kPitchSpriteOffset;
  static const std::string kPitchSpritePath;
  static const GraphicLayers kPitchSpriteLayer;
  static const bool kPitchEnabledAtStart;
  //------------------------Football pitch

  //-----------------------Input System
  static constexpr float kKeyCooldown = 0.008f;
  //-----------------------Input System

  //----------------------Button
  const static Vector_Float kButtonOffset;
  static const std::string kButtonSpritePath;
  static const Vector_Float kButtonSpriteOffset;
  static const Vector_Float kButtonLabelOffset;
  static const std::string kButtonFontPath;
  static const SDL_Color kButtonFontColor;
  static const int kButtonFontSize;
  static const GraphicLayers kButtonLayer;
  //----------------------//Button

  //------------------------Buttons
  static const Vector_Float kContinueButtonPos;
  static const std::string kContinueButtonText;
  static const std::string kContinueButtonTag;

  static const Vector_Float kOptionsButtonPos;
  static const std::string kOptionsButtonText;
  static const std::string kOptionsButtonTag;

  static const Vector_Float kQuitButtonPos;
  static const std::string kQuitButtonText;
  static const std::string kQuitButtonTag;
  //------------------------//Buttons

  //---------------------Menu
  static const bool kMenuEnabledAtStart;
  //---------------------//Menu

  //---------------------Player Sprite
  static const Vector_Float kPlayerSpriteOffset;
  static const GraphicLayers kPlayerSpriteLayer;
  static const bool kPlayerEnabledAtStart;
  static const std::string kPlayerSpritePath_Team1;
  static const std::string kPlayerSpritePath_Team2;
  //----------------------//Player Sprite

  //----------------------Ball
  static const Vector_Float kBallSpriteOffset;
  static const GraphicLayers kBallSpriteLayer;
  static const bool kBallEnabledAtStart;
  static const std::string kBallSpritePath;
  //-----------------------//Ball

  //-----------------------Selection Arrow
  static const Vector_Float kArrowSpriteOffset;
  static const GraphicLayers kArrowSpriteLayer;
  static const bool kArrowEnabledAtStart;
  static const std::string kArrowSpritePath;
  //------------------------Selection Arrow

  //----------------------Menu Panel
  static const Vector_Float kMenuPanelPosition;
  static const int kMenuPanelXOffset;
  static const int kMenuPanelYOffset;
  static const int kMenuPanelWidth;
  static const int kMenuPanelHeight;
  static const SDL_Color kMenuPanelColor;
  static const GraphicLayers kMenuPanelLayer;
  //-----------------------//Menu Panel

  //------------------------Player Label
  static const Vector_Float kPlayerLabelOffset;
  static const std::string kPlayerLabelFontPath;
  static const SDL_Color kPlayerLabelFontColor;
  static const int kPlayerLabelFontSize;
  static const GraphicLayers kPlayerLabelLayer;

  //-------------------------//Player Label

  //-------------------------Labels
  static const Vector_Float kLabelPosition;
  static const Vector_Float kLabelOffset;
  static const std::string kLabelFontPath;
  static const SDL_Color kLabelFontColor;
  static const int kLabelFontSize;
  static const GraphicLayers kLabelLayer;
  static const std::string kGameoverLabelText;
  static const std::string kScored1LabelText;
  static const std::string kScored2LabelText;
  static const std::string kGameoverLabelTag;
  static const std::string kScored1LabelTag;
  static const std::string kScored2LabelTag;

  static constexpr float kLabelHideTime = 2.5f;

  //------------------------//Labels

  //------------------------ client constants

  static constexpr Uint32 kClientNetworkReceiverDt = 8;

  //--------------------------// client constants
};
#endif // PV264_PROJECT_CLIENTGAMECONSTANTS_H
