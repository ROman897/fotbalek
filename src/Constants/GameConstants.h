//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_GAMECONSTANTS_H
#define PV264_PROJECT_GAMECONSTANTS_H

#include "../Utils/Declarations.h"
#include <SDL_pixels.h>
#include <SDL_quit.h>

struct GameConstants {

  static constexpr Uint32 kEngineAccumulatorLimit = 20U;
  static constexpr float kEngineFps = 60;
  static constexpr float kEngineDeltaTime = 1 / kEngineFps;
};

#endif // PV264_PROJECT_GAMECONSTANTS_H
