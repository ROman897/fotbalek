//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_GAMECONSTANTS_H
#define PV264_PROJECT_GAMECONSTANTS_H


#include <SDL_quit.h>
#include <SDL_pixels.h>
#include "declarations.h"

struct GameConstants {

    // how often is physic update run
    constexpr static double kFps = 100;
    constexpr static double kDeltaTime = 1 / kFps;
    constexpr static Uint32 kAccumulatorLimit = 20U;
    constexpr static Uint32 kInputCooldown = 10U;
    constexpr static float kInputMovementCoefficient = 10.0f;
    constexpr static int kWindowHeight = 800;
    constexpr static int kWindowWidth = 1200;
    const static Vector_Float kButtonOffset;

    static const std::string kPitchSpritePath;
    static constexpr float kKeyCooldown = 0.02f;
    static const std::string kButtonSpritePath;
    static const Vector_Float kButtonSpriteOffset;
    static const Vector_Float kButtonLabelOffset;
    static const std::string kButtonFontPath;
    static const SDL_Color kButtonFontColor;
    static const int kButtonFontSize;

};


#endif //PV264_PROJECT_GAMECONSTANTS_H
