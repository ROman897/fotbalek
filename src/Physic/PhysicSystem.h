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
#include "../SettingsDefines.h"
#include "../Components/Physic/ColliderTrigger.h"


inline void resolveCollision(const Collision &collision) {
    //std::cout << "resolve collision" << std::endl;
    Vector_Float vDiff = collision.second.m_velocity - collision.first.m_velocity;

    float velNormal = DotProduct( vDiff, collision.normal);

    if(velNormal > 0)
        return;

    // Calculate restitution, choose lower of the two restitutions
    float r = std::min( collision.first.m_restitution, collision.second.m_restitution);

    // Calculate impulse scalar
    float TotalForce = -(1 + r) * velNormal;
    // now multiply total force by masses
    TotalForce /= collision.first.m_inverseMass + collision.second.m_inverseMass;

    // Apply impulse
    Vector_Float impulse = collision.normal * TotalForce;

    // apply impulse, so add to velocities force relative to mass of the rigid body
    collision.first.m_velocity -= impulse * collision.first.m_inverseMass;
    collision.second.m_velocity += impulse * collision.second.m_inverseMass;

}

inline float Clamp(float min, float max, float val) {
    return std::abs(min - val) < std::abs(max - val) ? min : max;
}





inline bool checkForCollisionCircle_Circle(const CircleCollider* shape1, const Transform* transform1,
                                           const CircleCollider* shape2, const Transform* transform2,
                                            Collision* collision, bool trigger){


    // Vector from A to B
    Vector_Float n = transform2->m_position - transform1->m_position;

    float r = shape1->m_radius + shape2->m_radius;
    r *= r;

    if(n.lengthSquared() > r)
        return false;
    if (trigger)
        return true;

    float d = n.length();

    // If distance between circles is not zero
    if(d != 0)
    {
        // Distance is difference between radius and distance
        collision->penetration = r - d;

        // now we have to calculate vector perpendicular to vector n and normalize it
        Vector_Float normal = n.getNormal();
        collision->normal = normal / d;

    }

        // Circles are on same position
    else
    {
        // this should not be really happening, but just in case when distance is 0 so we dont divide by 0
        collision->penetration = shape1->m_radius;
        collision->normal = Vector_Float( 1, 0 );
    }
    return true;
}


inline bool checkForCollisionRectangle_Rectangle(const RectangleCollider* shape1, const Transform* transform1, const RectangleCollider* shape2,
                                          const Transform* transform2, Collision* collision, bool trigger){

    //std::cout << "pos1 x: " << transform1->m_position.m_x << " y : " << transform1->m_position.m_y << std::endl;
    //std::cout << "pos2 x: " << transform2->m_position.m_x << " y : " << transform2->m_position.m_y << std::endl;

    //std::cout << "vel1 x: " << body1->m_velocity.m_x << " y : " << body1->m_velocity.m_y << std::endl;
    //std::cout << "vel2 x: " << body2->m_velocity.m_x << " y : " << body2->m_velocity.m_y << std::endl;
    Vector_Float n = transform2->m_position - transform1->m_position;
    //std::cout << "length: " << n.length() << std::endl;

    float collider1_X = (shape1->m_bottomRight.m_x
                          - shape1->m_topLeft.m_x
                         ) / 2;
    float collider2X = (shape2->m_bottomRight.m_x
                         - shape2->m_topLeft.m_x
                        ) / 2;
    float x_overlap = collider1_X + collider2X - std::abs( n.m_x
    );
    //std::cout << "collider1 x: " << collider1_X << std::endl;
    //std::cout << "x overlap: " << x_overlap << std::endl;


    float collider1_Y = (shape1->m_topLeft.m_y
                          - shape1->m_bottomRight.m_y
                         ) / 2;
    float collider2_Y = (shape2->m_topLeft.m_y
                          - shape2->m_bottomRight.m_y
                         ) / 2;
    float y_overlap = collider1_Y + collider2_Y - std::abs( n.m_y
    );

    // this means that no collision occured
    if (x_overlap <=0 && y_overlap <= 0)
        return false;
    if (trigger)
        return true;

    //std::cout << "overlap" << std::endl;

    // for rectangles this means that we only solve collision in one axis, the one that has greater overlap
    if(x_overlap > y_overlap)
    {
        if(n.m_x
           < 0)
            collision->normal = Vector_Float(-1, 0);
        else
            collision->normal = Vector_Float( 1, 0 );
        collision->penetration = x_overlap;
    }
    else
    {
        if(n.m_y
           < 0)
            collision->normal = Vector_Float( 0, -1 );
        else
            collision->normal = Vector_Float( 0, 1 );
        collision->penetration = y_overlap;
    }

    return true;
}


inline bool checkForCollisionRectangle_Circle(const RectangleCollider* shape1, const Transform* transform1, const CircleCollider* shape2,
                                       const Transform* transform2, Collision* collision, bool trigger){

    Vector_Float n = transform2->m_position - transform1->m_position;
    Vector_Float closest = n;
    float x_extent = (shape1->m_topLeft.m_x
                       - shape1->m_bottomRight.m_x
                      ) / 2;
    float y_extent = (shape1->m_topLeft.m_y
                       - shape1->m_bottomRight.m_y
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

    Vector_Float normal = n - closest;
    float d = normal.lengthSquared();
    float r = shape2->m_radius;

    if(d > r * r && !inside)
        return false;

    if (trigger)
        return true;
    d = std::sqrt( d );
    if(inside)
    {
        collision->normal = n * -1;
        collision->penetration = r - d;
    }
    else
    {
        collision->normal = n;
        collision->penetration = r - d;
    }
    return true;
}




inline void processTriggerCollisionRectangle_Circle(const RectangleCollider* shape1, const Transform* transform1, ColliderTrigger trigger,
                                                    const CircleCollider* shape2, const Transform* transform2){

}

inline void processTriggerCollisionRectangle_Rectangle(const RectangleCollider* shape1, const Transform* transform1, ColliderTrigger trigger,
                                                    const RectangleCollider* shape2, const Transform* transform2){

}

inline void processTriggerCollisionCircle_Circle(const CircleCollider* shape1, const Transform* transform1, ColliderTrigger* trigger,
                                                    const CircleCollider* shape2, const Transform* transform2){
    if (! checkForCollisionCircle_Circle(shape1, transform1, shape2,
                                          transform2, nullptr, true))
        return;
    for (auto& func : trigger->m_callbacks){
        func();
    }

}


inline void processCollisionRectangle_Circle(const RectangleCollider* shape1, RigidBody* body1, const Transform* transform1, const CircleCollider* shape2,
                                              RigidBody* body2, const Transform* transform2){
    Collision collision(*body1, *body2);
    if (checkForCollisionRectangle_Circle(shape1, transform1, shape2,
    transform2, &collision, false))
        resolveCollision(collision);

}


inline void processCollisionRectangle_Rectangle(const RectangleCollider* shape1, RigidBody* body1, const Transform* transform1, const RectangleCollider* shape2,
                                                             RigidBody* body2, const Transform* transform2){
    Collision collision(*body1, *body2);
    if (checkForCollisionRectangle_Rectangle(shape1, transform1, shape2,
                                          transform2, &collision, false))
        resolveCollision(collision);
}



inline void processCollisionCircle_Circle(const CircleCollider* shape1, RigidBody* body1,
                                           const Transform* transform1, const CircleCollider* shape2, RigidBody* body2, const Transform* transform2) {

    Collision collision(*body1, *body2);
    if (checkForCollisionCircle_Circle(shape1, transform1, shape2,
                                             transform2, &collision, false))
        resolveCollision(collision);
}












template <typename TSettings>
class PhysicSystem {
private:
    ComponentManager<TSettings>* componentManager;

public:
    //void start();
    /*using SystemSignature_Movable = Signature<RigidBody, Transform>;
    using SystemSignature_Circle_Collider = Signature <CircleCollider, RigidBody, Transform>;
    using SystemSignature_Rectangle_Collider = Signature <RectangleCollider, RigidBody, Transform>;*/


    void setManager(ComponentManager<TSettings>* manager){
        componentManager = manager;
    }












/*void PhysicSystem::runMovements(RigidBody& rigidBody, Transform& transform){
    transform.position += rigidBody.m_velocity * dt;
}*/

    void run(float dt){
        runPhysicUpdate(dt);
    }

    void runPhysicUpdate(float dt) {
        //std::cout << "run physic update" << std::endl;
        //std::cout << "run physic update" << std::endl;

        componentManager->template forEntitiesMatching<SystemSignature_Movable>([dt](RigidBody* rigidBody, Transform* transform){
            transform->m_position += rigidBody->m_velocity * dt;
            rigidBody->m_velocity /= rigidBody->m_speedDecrement;
        });

        componentManager->template forEntitiesMatchingPairs<SystemSignature_Circle_Collider, SystemSignature_Circle_Collider>(processCollisionCircle_Circle);
        componentManager->template forEntitiesMatchingPairs<SystemSignature_Rectangle_Collider, SystemSignature_Rectangle_Collider>(processCollisionRectangle_Rectangle);
        componentManager->template forEntitiesMatchingPairs<SystemSignature_Rectangle_Collider, SystemSignature_Circle_Collider>(processCollisionRectangle_Circle);
    }

    void start() {

        Uint32 accumulator = 0;
        Timer timer;
        timer.start();


        float frameStart = timer.getTime();
        timer.resetTime();


        while( true ) {
            if (componentManager->shouldQuit())
                return;
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
