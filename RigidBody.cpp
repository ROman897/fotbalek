//
// Created by roman on 4.4.2017.
//

#include "RigidBody.h"

void RigidBody::applyForce(Vector2 force) {
    activeForce += force;
}

Shape *RigidBody::getShape() const {
    return shape;
}

const Vector2 &RigidBody::getPosition() const {
    return position;
}

const Vector2 &RigidBody::getVelocity() const {
    return velocity;
}

double RigidBody::getRestitution() const {
    return restitution;
}

void RigidBody::setRestitution(double restitution) {
    RigidBody::restitution = restitution;
}

double RigidBody::getInverseMass() const {
    return inverseMass;
}

void RigidBody::update(double dt) {
    velocity += activeForce * inverseMass;
    velocity /= speedDecrement;
}
