//
// Created by roman on 19.4.2017.
//

#ifndef PV264_PROJECT_INPUTHOLDER_H
#define PV264_PROJECT_INPUTHOLDER_H

#include <vector>
#include <SDL_events.h>

struct MovementInputHolder{
    bool moveUp;
    bool moveDown;
    bool moveRight;
    bool moveLeft;
    bool shoot;
    bool valid;
};
#endif //PV264_PROJECT_INPUTHOLDER_H
