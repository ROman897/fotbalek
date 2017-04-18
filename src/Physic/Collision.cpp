//
// Created by roman on 4.4.2017.
//

#include "Collision.h"

Collision::Collision(RigidBody &first, RigidBody &second, double penetration, const Vector_Int &normal) : first(first),
                                                                                                       second(second),
                                                                                                       penetration(
                                                                                                               penetration),
                                                                                                       normal(normal) {}

Collision::Collision(RigidBody &first, RigidBody &second) : first(first), second(second) {}
