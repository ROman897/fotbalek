//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_PHYSICENGINE_H
#define PV264_PROJECT_PHYSICENGINE_H


#include <vector>
#include "RigidBody.h"
#include "GameConstants.h"
#include "Circle.h"
#include "Rectangle.h"
#include <cmath>

class PhysicEngine {
private:
    // physic engine need view of all gameobjects that phusically interact with each other
    std::vector<RigidBody*> bodies;
    bool quit;

public:
    void run();

private:
    void runPhysicUpdate(double dt);

    void checkForCollision(RigidBody* body1, RigidBody* body2);

    // force compiler to automatically deduce types of SHAPE1 and SHAPE2 by passing shapes of the rigidbodies
    template <typename SHAPE1, typename SHAPE2>
    void _checkForCollision(const SHAPE1& shape1, const SHAPE2& shape2, RigidBody* body1, RigidBody* body2){
        // here we do nothing
    };

    // so we can now implement specific behaviour for each method using template specification





    double Clamp(double min, double max, double val);
    void resolveCollision(const Collision& collision);


};


#endif //PV264_PROJECT_PHYSICENGINE_H
