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
    //bool m_isTrigger;

    RigidBody() = default;
    RigidBody(float m_inverseMass, float m_restitution, const Vector_Float &m_velocity,
              const Vector_Float &m_activeForce, float m_speedDecrement) : m_inverseMass(m_inverseMass),
                                                                            m_restitution(m_restitution),
                                                                            m_velocity(m_velocity),
                                                                            m_activeForce(m_activeForce),
                                                                            m_speedDecrement(m_speedDecrement) {}

    RigidBody(float m_inverseMass, float m_restitution, float m_speedDecrement) : m_inverseMass(m_inverseMass),
                                                                                  m_restitution(m_restitution),
                                                                                  m_velocity({0,0}),
                                                                                  m_activeForce({0,0}),
                                                                                  m_speedDecrement(m_speedDecrement) {}

    //Material material;
    //MassData mass_data;
    float m_inverseMass;


    float m_restitution;

    // this vector represents actual direction and speed of rigid body
    Vector_Float m_velocity;

    // this vector represents forces to be applied to this rigid body in this frame
    Vector_Float m_activeForce;

    // every frame speed of an object will be decreased by some amount
    float m_speedDecrement;
};


#endif //PV264_PROJECT_RIGIDBODY_H
