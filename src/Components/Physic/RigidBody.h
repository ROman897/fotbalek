//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_RIGIDBODY_H
#define PV264_PROJECT_RIGIDBODY_H

#include "../../Utils/Vector2.h"
#include "../../Utils/declarations.h"

//class Shape;

struct RigidBody {

    // rigidbodies marked as trigger will not directly react to collision,
    // they will only call OnCollision callback.
    // this behaviour is to be used for collision checking, such as to check whether ball is in the goal
    bool m_isTrigger;


    //Material material;
    //MassData mass_data;
    double m_inverseMass;


    double m_restitution;

    // this vector represents actual direction and speed of rigid body
    Vector_Int m_velocity;

    // this vector represents forces to be applied to this rigid body in this frame
    Vector_Int m_activeForce;

    // every frame speed of an object will be decreased by some amount
    double m_speedDecrement;
};


#endif //PV264_PROJECT_RIGIDBODY_H
