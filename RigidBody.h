//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_RIGIDBODY_H
#define PV264_PROJECT_RIGIDBODY_H

#include "Vector2.h"
#include "Shape.h"

class Shape;

class RigidBody {
    Shape *shape;
    Vector2 position;


    //Material material;
    //MassData mass_data;
    double inverseMass;
public:
    double getInverseMass() const;

private:
    double restitution;
public:
    double getRestitution() const;

    void setRestitution(double restitution);

public:
    const Vector2 &getPosition() const;

private:
public:
    const Vector2 &getVelocity() const;

private:

    // this vector represents actual direction and speed of rigid body
    Vector2 velocity;

    // this vector represents forces to be applied to this rigid body in this frame
    Vector2 activeForce;

    // every frame speed of an object will be decreased by some amount
    double speedDecrement;

public:
    Shape *getShape() const;
    void applyForce(Vector2 force);
    void update(double dt);
};


#endif //PV264_PROJECT_RIGIDBODY_H
