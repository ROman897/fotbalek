//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_PHYSICENGINE_H
#define PV264_PROJECT_PHYSICENGINE_H


#include <vector>
#include "../Components/Physic/RigidBody.h"
#include "../Utils/GameConstants.h"
#include "../Components/Physic/Shapes/CircleCollider.h"
#include "../Components/Physic/Shapes/RectangleCollider.h"
#include "Collision.h"
#include <cmath>
#include "../Utils/declarations.h"
#include "../Components/Transform.h"
#include "../Core/ComponentManager.h"
#include "../Utils/Timer.h"


inline void resolveCollision(const Collision &collision) {
    Vector_Int vDiff = collision.second.m_velocity - collision.first.m_velocity;

    double velNormal = DotProduct( vDiff, collision.normal);

    if(velNormal > 0)
        return;

    // Calculate restitution, choose lower of the two restitutions
    double r = std::min( collision.first.m_restitution, collision.second.m_restitution);

    // Calculate impulse scalar
    double TotalForce = -(1 + r) * velNormal;
    // now multiply total force by masses
    TotalForce /= collision.first.m_inverseMass + collision.second.m_inverseMass;

    // Apply impulse
    Vector_Int impulse = collision.normal * TotalForce;

    // apply impulse, so add to velocities force relative to mass of the rigid body
    collision.first.m_velocity -= impulse * collision.first.m_inverseMass;
    collision.second.m_velocity += impulse * collision.second.m_inverseMass;

}

double Clamp(double min, double max, double val) {
    return std::abs(min - val) < std::abs(max - val) ? min : max;
}





inline void checkForCollisionCircle_Circle(const CircleCollider& shape1, RigidBody& body1, const Transform& transform1, const CircleCollider& shape2, RigidBody& body2, const Transform& transform2){


    // Vector from A to B
    Vector_Int n = transform2.m_position - transform1.m_position;

    double r = shape1.m_radius + shape2.m_radius;
    r *= r;

    if(n.lengthSquared() > r)
        return;

    Collision collision(body1, body2);

    double d = n.length();

    // If distance between circles is not zero
    if(d != 0)
    {
        // Distance is difference between radius and distance
        collision.penetration = r - d;

        // now we have to calculate vector perpendicular to vector n and normalize it
        Vector_Int normal = n.getNormal();
        collision.normal = normal / d;

    }

        // Circles are on same position
    else
    {
        // this should not be really happening, but just in case when distance is 0 so we dont divide by 0
        collision.penetration = shape1.m_radius;
        collision.normal = Vector_Int( 1, 0 );
    }
    resolveCollision(collision);
}


inline void checkForCollisionRectangle_Rectangle(const RectangleCollider& shape1, RigidBody& body1, const Transform& transform1, const RectangleCollider& shape2,
                                          RigidBody& body2, const Transform& transform2){


    Vector_Int n = transform2.m_position - transform1.m_position;

    double collider1_X = (shape1.m_topLeft.m_x
                          - shape1.m_bottomRight.m_x
                         ) / 2;
    double collider2X = (shape2.m_topLeft.m_x
                         - shape2.m_bottomRight.m_x
                        ) / 2;
    double x_overlap = collider1_X + collider2X - std::abs( n.m_x
    );


    double collider1_Y = (shape1.m_topLeft.m_y
                          - shape1.m_bottomRight.m_y
                         ) / 2;
    double collider2_Y = (shape2.m_topLeft.m_y
                          - shape2.m_bottomRight.m_y
                         ) / 2;
    double y_overlap = collider1_Y + collider2_Y - std::abs( n.m_y
    );

    // this means that no collision occured
    if (x_overlap <=0 && y_overlap <= 0)
        return;

    Collision collision(body1, body2);

    // for rectangles this means that we only solve collision in one axis, the one that has greater overlap
    if(x_overlap > y_overlap)
    {
        if(n.m_x
           < 0)
            collision.normal = Vector_Int(-1, 0);
        else
            collision.normal = Vector_Int( 1, 0 );
        collision.penetration = x_overlap;
    }
    else
    {
        if(n.m_y
           < 0)
            collision.normal = Vector_Int( 0, -1 );
        else
            collision.normal = Vector_Int( 0, 1 );
        collision.penetration = y_overlap;
    }

    resolveCollision(collision);
}


inline void checkForCollisionRectangle_Circle(const RectangleCollider& shape1, RigidBody& body1, const Transform& transform1, const CircleCollider& shape2,
                                       RigidBody& body2, const Transform& transform2){

    Vector_Int n = transform2.m_position - transform1.m_position;
    Vector_Int closest = n;
    double x_extent = (shape1.m_topLeft.m_x
                       - shape1.m_bottomRight.m_x
                      ) / 2;
    double y_extent = (shape1.m_topLeft.m_y
                       - shape1.m_bottomRight.m_y
                      ) / 2;

    closest.m_x
            = Clamp( -x_extent, x_extent, closest.m_x
    );
    closest.m_y
            = Clamp( -y_extent, y_extent, closest.m_y
    );

    bool inside = false;

    if(n == closest)
    {
        inside = true;

        if(std::abs( n.m_x
        ) > std::abs( n.m_y
        ))
        {
            if(closest.m_x
               > 0)
                closest.m_x
                        = x_extent;
            else
                closest.m_x
                        = -x_extent;
        }

        else
        {

            if(closest.m_y
               > 0)
                closest.m_y
                        = y_extent;
            else
                closest.m_y
                        = -y_extent;
        }
    }

    Vector_Int normal = n - closest;
    double d = normal.lengthSquared();
    double r = shape2.m_radius;

    if(d > r * r && !inside)
        return;

    d = std::sqrt( d );

    Collision collision(body1, body2);
    if(inside)
    {
        collision.normal = n * -1;
        collision.penetration = r - d;
    }
    else
    {
        collision.normal = n;
        collision.penetration = r - d;
    }
    resolveCollision(collision);
}


















template <typename TSettings>
class PhysicSystem {
private:
    // physic engine has view of all gameobjects that physically interact with each other
    // TODO decide how to represent actual positions and positions to draw

    bool quit;
    ComponentManager<TSettings>& componentManager;

public:
    //void start();
    using SystemSignature_Movable = Signature<RigidBody, Transform>;
    using SystemSignature_Circle_Collider = Signature <CircleCollider, RigidBody, Transform>;
    using SystemSignature_Rectangle_Collider = Signature <RectangleCollider, RigidBody, Transform>;
    //using SystemSignature_Circle_Immovable = Signature <CircleCollider, Transform>;
    //using SystemSignature_Rectangle_Immovable = Signature <RectangleCollider, Transform>;

private:
    //void runPhysicUpdate(double dt);












/*void PhysicSystem::runMovements(RigidBody& rigidBody, Transform& transform){
    transform.position += rigidBody.m_velocity * dt;
}*/

    void runPhysicUpdate(double dt) {

        componentManager.template forEntitiesMatching<SystemSignature_Movable>([dt](RigidBody& rigidBody, Transform& transform){
            transform.m_position += rigidBody.m_velocity * dt;
            rigidBody.m_velocity /= rigidBody.m_speedDecrement;
        });

        componentManager.template forEntitiesMatchingPairs<SystemSignature_Circle_Collider, SystemSignature_Circle_Collider>(checkForCollisionCircle_Circle);
        componentManager.template forEntitiesMatchingPairs<SystemSignature_Rectangle_Collider, SystemSignature_Rectangle_Collider>(checkForCollisionRectangle_Rectangle);
        componentManager.template forEntitiesMatchingPairs<SystemSignature_Rectangle_Collider, SystemSignature_Circle_Collider>(checkForCollisionRectangle_Circle);
    }

    void start() {

        double accumulator = 0;
        Timer timer;


        float frameStart = timer.getTime();
        timer.resetTime();


        while( !quit ) {
            accumulator += timer.getTime() - frameStart;

            frameStart = timer.getTime();

            if (accumulator > GameConstants::kAccumulatorLimit)
                accumulator = GameConstants::kAccumulatorLimit;

            while (accumulator > GameConstants::kDeltaTime) {
                runPhysicUpdate(GameConstants::kDeltaTime);
                accumulator -= GameConstants::kDeltaTime;
            }
        }

    }
};


#endif //PV264_PROJECT_PHYSICENGINE_H
