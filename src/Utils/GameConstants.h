//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_GAMECONSTANTS_H
#define PV264_PROJECT_GAMECONSTANTS_H


#include <SDL_quit.h>

struct GameConstants {

    // how often is physic update run
    constexpr static double kFps = 100;
    constexpr static double kDeltaTime = 1 / kFps;
    constexpr static Uint32 kAccumulatorLimit = 20U;
    constexpr static Uint32 kInputCooldown = 10U;
    constexpr static float kInputMovementCoefficient = 10.0f;
    constexpr static int kWindowHeight = 800;
    constexpr static int kWindowWidth = 1200;

};


#endif //PV264_PROJECT_GAMECONSTANTS_H
