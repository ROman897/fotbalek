//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_GAMECONSTANTS_H
#define PV264_PROJECT_GAMECONSTANTS_H


struct GameConstants {

    // how often is physic update run
    constexpr static const double kFps = 100;
    constexpr static const double kDeltaTime = 1 / kFps;
    constexpr static const double kAccumulatorLimit = 0.2;

};


#endif //PV264_PROJECT_GAMECONSTANTS_H
