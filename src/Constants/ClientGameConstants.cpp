#include "ClientGameConstants.h"

//-------------------------Football pitch
const std::string ClientGameConstants::kPitchSpritePath = "../Resources/Sprites/Pitch.png";
const Vector_Float ClientGameConstants::kPitchPos = {50,50};
const Vector_Float ClientGameConstants::kPitchSpriteOffset = {0,0};
const GraphicLayers ClientGameConstants::kPitchSpriteLayer = BACKGROUND;
const bool ClientGameConstants::kPitchEnabledAtStart = true;
//--------------------------//Football pitch

//----------------------Button
const Vector_Float ClientGameConstants::kButtonOffset = {-40, 20};
const std::string ClientGameConstants::kButtonSpritePath = "../Resources/Sprites/Button.png";
const Vector_Float ClientGameConstants::kButtonSpriteOffset = {0, -32};
const Vector_Float ClientGameConstants::kButtonLabelOffset = {50, 70};
const std::string ClientGameConstants::kButtonFontPath = "../Resources/Fonts/BasicFont.ttf";
const SDL_Color ClientGameConstants::kButtonFontColor = {255, 0, 0, 255};
const int ClientGameConstants::kButtonFontSize = 22;
const GraphicLayers ClientGameConstants::kButtonLayer = FRONTUI;
//---------------------//Button


//---------------------Menu
const bool ClientGameConstants::kMenuEnabledAtStart = false;
//---------------------//Menu

//------------------------Menu Panel
const Vector_Float ClientGameConstants::kMenuPanelPosition = {225,50};
const int ClientGameConstants::kMenuPanelXOffset = 0;
const int ClientGameConstants::kMenuPanelYOffset = 0;
const int ClientGameConstants::kMenuPanelWidth = 600;
const int ClientGameConstants::kMenuPanelHeight = 600;
const SDL_Color ClientGameConstants::kMenuPanelColor = {0,0,0,255};
const GraphicLayers ClientGameConstants::kMenuPanelLayer = BACKUI;
//------------------------//Menu Panel

//---------------------Player Sprite
const Vector_Float ClientGameConstants::kPlayerSpriteOffset = {32,32};
const GraphicLayers ClientGameConstants::kPlayerSpriteLayer = FOREGROUND;
const bool ClientGameConstants::kPlayerEnabledAtStart = false;
const std::string ClientGameConstants::kPlayerSpritePath_Team1 = "../Resources/Sprites/Player1.png";
const std::string ClientGameConstants::kPlayerSpritePath_Team2 = "../Resources/Sprites/Player2.png";
//----------------------//Player Sprite


//------------------------Player Label
const Vector_Float ClientGameConstants::kPlayerLabelOffset = {0,40};
const std::string ClientGameConstants::kPlayerLabelFontPath = "../Resources/Fonts/BasicFont.ttf";
const SDL_Color ClientGameConstants::kPlayerLabelFontColor = {0,0,0,255};
const int ClientGameConstants::kPlayerLabelFontSize = 16;
const GraphicLayers ClientGameConstants::kPlayerLabelLayer = FOREGROUND;

//-------------------------//Player Label

//-------------------------Labels
const Vector_Float ClientGameConstants::kLabelPosition = {400, 300};
const Vector_Float ClientGameConstants::kLabelOffset = {0,0};
const std::string ClientGameConstants::kLabelFontPath = "../Resources/Fonts/BasicFont.ttf";
const SDL_Color ClientGameConstants::kLabelFontColor = {255,0,0,255};
const int ClientGameConstants::kLabelFontSize = 40;
const GraphicLayers ClientGameConstants::kLabelLayer = MISC;
const std::string ClientGameConstants::kGameoverLabelText = "GAME OVER";
const std::string ClientGameConstants::kScored1LabelText = "TEAM 1 SCORED";
const std::string ClientGameConstants::kScored2LabelText = "TEAM 2 SCORED";
const std::string ClientGameConstants::kGameoverLabelTag = "gameover";
const std::string ClientGameConstants::kScored1LabelTag = "scored1";
const std::string ClientGameConstants::kScored2LabelTag = "scored2";

//------------------------//Labels





//-----------------------Selection Arrow
const Vector_Float ClientGameConstants::kArrowSpriteOffset = {0,50};
const GraphicLayers ClientGameConstants::kArrowSpriteLayer = FRONTUI;
const bool ClientGameConstants::kArrowEnabledAtStart = false;
const std::string ClientGameConstants::kArrowSpritePath = "../Resources/Sprites/Ball.png";
//------------------------Selection Arrow


//----------------------Ball
const Vector_Float ClientGameConstants::kBallSpriteOffset = {32,32};
const GraphicLayers ClientGameConstants::kBallSpriteLayer = FOREGROUND;
const bool ClientGameConstants::kBallEnabledAtStart = false;
const std::string ClientGameConstants::kBallSpritePath = "../Resources/Sprites/Ball.png";
//-----------------------//Ball



//------------------------Buttons
const Vector_Float ClientGameConstants::kContinueButtonPos = {400, 100};
const std::string ClientGameConstants::kContinueButtonText = "CONTINUE";
const std::string ClientGameConstants::kContinueButtonTag = "continue";

const Vector_Float ClientGameConstants::kOptionsButtonPos = {400, 200};
const std::string ClientGameConstants::kOptionsButtonText = "OPTIONS";
const std::string ClientGameConstants::kOptionsButtonTag = "options";

const Vector_Float ClientGameConstants::kQuitButtonPos = {400, 300};
const std::string ClientGameConstants::kQuitButtonText = "QUIT GAME";
const std::string ClientGameConstants::kQuitButtonTag = "quit";
//------------------------//Buttons