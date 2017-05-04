#include "ClientGameConstants.h"

//-------------------------Football pitch
const std::string ClientGameConstants::kPitchSpritePath = "../Resources/Sprites/Pitch.png";
//--------------------------//Football pitch

//----------------------Button
const Vector_Float ClientGameConstants::kButtonOffset = {-40, 20};
const std::string ClientGameConstants::kButtonSpritePath = "../Resources/Sprites/Button.png";
const Vector_Float ClientGameConstants::kButtonSpriteOffset = {0, -32};
const Vector_Float ClientGameConstants::kButtonLabelOffset = {50, 70};
const std::string ClientGameConstants::kButtonFontPath = "../Resources/Fonts/BasicFont.ttf";
const SDL_Color ClientGameConstants::kButtonFontColor = {255, 0, 0, 255};
const int ClientGameConstants::kButtonFontSize = 22;
const GraphicLayers ClientGameConstants::kButtonLayer = FOREGROUND;
//---------------------//Button


//------------------------Player Sprite
const std::string ClientGameConstants::kPlayerSpritePath_Team1 = "../Resources/Sprites/Player1.png";
const std::string ClientGameConstants::kPlayerSpritePath_Team2 = "../Resources/Sprites/Player2.png";
//-----------------------//Player Sprite

//---------------------Menu
const bool ClientGameConstants::kMenuEnabledAtStart = false;
//---------------------//Menu

//------------------------Menu Panel
const Vector_Float ClientGameConstants::kMenuPanelPosition = {200,200};
const int ClientGameConstants::kMenuPanelXOffset = 0;
const int ClientGameConstants::kMenuPanelYOffset = 0;
const int ClientGameConstants::kMenuPanelWidth = 600;
const int ClientGameConstants::kMenuPanelHeight = 600;
const SDL_Color ClientGameConstants::kMenuPanelColor = {0,0,0,255};
const GraphicLayers ClientGameConstants::kMenuPanelLayer = BACKUI;
//------------------------//Menu Panel

//-------------------------Client constants
const std::string ClientGameConstants::kServerPort = "13000";
const std::string ClientGameConstants::kServerAddress = "147.251.47.243";

//-------------------------//Client constants