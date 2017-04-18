//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_COLLISION_H
#define PV264_PROJECT_COLLISION_H

#include "../Components/Physic/RigidBody.h"

class RigidBody;

struct Collision {

    RigidBody& first;
    RigidBody& second;
    double penetration;

    Collision(RigidBody &first, RigidBody &second);

    Collision(RigidBody &first, RigidBody &second, double penetration, const Vector_Int &normal);

    Vector_Int normal;
};


#endif //PV264_PROJECT_COLLISION_H
