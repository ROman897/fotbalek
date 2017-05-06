//
// Created by roman on 19.4.2017.
//

#ifndef PV264_PROJECT_INPUTHOLDER_H
#define PV264_PROJECT_INPUTHOLDER_H

#include <vector>
#include <SDL_events.h>

struct MovementInputHolder{
    bool moveUp;
    bool moveVertical;
    bool moveRight;
    bool moveHorizontal;
    bool shoot;
    bool valid;

    MovementInputHolder() : moveVertical(false), moveHorizontal(false), valid(false) {

    }
};
#endif //PV264_PROJECT_INPUTHOLDER_H
