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
//---------------------//Button


//------------------------Player Sprite
const std::string ClientGameConstants::kPlayerSpritePath_Team1 = "../Resources/Sprites/Player1.png";
const std::string ClientGameConstants::kPlayerSpritePath_Team2 = "../Resources/Sprites/Player2.png";
//-----------------------//Player Sprite

//------------------------Menu Panel
const Vector_Float kMenuPanelPosition = {200,200};
const int kMenuPanelXOffset = 0;
const int kMenuPanelYOffset = 0;
const int kMenuPanelWidth = 600;
const int kMenuPanelHeight = 600;
const SDL_Color kMenuPanelColor = {0,0,0,255};
const GraphicLayers kMenuPanelLayer = BACKUI;
//------------------------//Menu Panel