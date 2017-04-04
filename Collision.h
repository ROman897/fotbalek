//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_COLLISION_H
#define PV264_PROJECT_COLLISION_H

#include "RigidBody.h"

class RigidBody;

struct Collision {

    RigidBody* first;
    RigidBody* second;
    double penetration;
    Vector2 normal;
};


#endif //PV264_PROJECT_COLLISION_H
