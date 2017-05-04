//
// Created by roman on 3.5.2017.
//

#ifndef PV264_PROJECT_CLIENTGAMECONSTANTS_H
#define PV264_PROJECT_CLIENTGAMECONSTANTS_H

#include <SDL_pixels.h>
#include "../Utils/declarations.h"

struct ClientGameConstants {

    //--------------------window
    constexpr static int kWindowHeight = 800;
    constexpr static int kWindowWidth = 1200;
    //--------------------//window

    //------------------------Football pitch
    static const std::string kPitchSpritePath;
    //------------------------Football pitch


    //-----------------------Input System
    static constexpr float kKeyCooldown = 0.02f;
    //-----------------------Input System


    //----------------------Button
    const static Vector_Float kButtonOffset;
    static const std::string kButtonSpritePath;
    static const Vector_Float kButtonSpriteOffset;
    static const Vector_Float kButtonLabelOffset;
    static const std::string kButtonFontPath;
    static const SDL_Color kButtonFontColor;
    static const int kButtonFontSize;
    //----------------------//Button


    //---------------------Player Sprite
    static const std::string kPlayerSpritePath_Team1;
    static const std::string kPlayerSpritePath_Team2;
    //----------------------//Player Sprite

};
#endif //PV264_PROJECT_CLIENTGAMECONSTANTS_H
