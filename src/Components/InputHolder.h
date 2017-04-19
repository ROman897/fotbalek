//
// Created by roman on 19.4.2017.
//

#ifndef PV264_PROJECT_INPUTHOLDER_H
#define PV264_PROJECT_INPUTHOLDER_H

#include <vector>
#include <SDL_events.h>

struct InputHolder{
    std::vector<SDL_Event> events;
};
#endif //PV264_PROJECT_INPUTHOLDER_H
