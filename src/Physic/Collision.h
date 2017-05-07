//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_COLLISION_H
#define PV264_PROJECT_COLLISION_H

#include "../Components/Physic/RigidBody.h"

//class RigidBody;

struct Collision {

    RigidBody& first;
    RigidBody& second;
    double penetration;
	Vector_Float normal;

    Collision(RigidBody &first, RigidBody &second) : first(first), second(second) {};

    Collision(RigidBody &first, RigidBody &second, double penetration, const Vector_Float &normal) : first(first),
    second(second),
    penetration(penetration),
    normal(normal) {};

};


#endif //PV264_PROJECT_COLLISION_H
