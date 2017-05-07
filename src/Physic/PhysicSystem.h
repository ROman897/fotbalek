//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_PHYSICENGINE_H
#define PV264_PROJECT_PHYSICENGINE_H


#include <vector>
#include "../Components/Physic/RigidBody.h"
#include "../Constants/GameConstants.h"
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
#include "../Constants/ServerGameConstants.h"


inline void resolveCollision(const Collision &collision) {
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
    collision.first.m_velocity.limitLength(collision.first.m_maxSpeed);
    collision.second.m_velocity.limitLength(collision.second.m_maxSpeed);

}

inline float Clamp(float min, float max, float middle, float val) {
    float v = std::abs(min - val) < std::abs(max - val) ? min : max;
    return std::abs(v - val) < std::abs(middle - val) ? v : middle;

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
    if(d != 0) {
        // Distance is difference between radius and distance
        collision->penetration = r - d;

        // now we have to calculate vector perpendicular to vector n and normalize it
        Vector_Float normal = n.getNormal();
        collision->normal = normal / d;

    } else {
        // Circles are on same position
        // this should not be really happening, but just in case when distance is 0 so we dont divide by 0
        collision->penetration = shape1->m_radius;
        collision->normal = Vector_Float( 1, 0 );
    }

    return true;
}


inline bool checkForCollisionRectangle_Rectangle(const RectangleCollider* shape1, const Transform* transform1, const RectangleCollider* shape2,
                                          const Transform* transform2, Collision* collision, bool trigger){

    Vector_Float n = transform2->m_position - transform1->m_position;

    float collider1_X = (shape1->m_bottomRight.m_x - shape1->m_topLeft.m_x) / 2;
    float collider2X = (shape2->m_bottomRight.m_x - shape2->m_topLeft.m_x) / 2;
    float x_overlap = collider1_X + collider2X - std::abs( n.m_x );


    float collider1_Y = ( shape1->m_bottomRight.m_y - shape1->m_topLeft.m_y ) / 2;
    float collider2_Y = ( shape2->m_bottomRight.m_y - shape2->m_topLeft.m_y ) / 2;
    float y_overlap = collider1_Y + collider2_Y - std::abs( n.m_y );

    // this means that no collision occured
    if (x_overlap <= 0 || y_overlap <= 0)
        return false;
    if (trigger)
        return true;

    // for rectangles this means that we only solve collision in one axis, the one that has greater overlap
    if(y_overlap > x_overlap) {
        if(n.m_x < 0)
            collision->normal = Vector_Float(-1, 0);
        else
            collision->normal = Vector_Float( 1, 0 );
        collision->penetration = x_overlap;
    } else {
        if(n.m_y < 0)
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
    float x_extent = (shape1->m_bottomRight.m_x - shape1->m_topLeft.m_x) / 2;
    float y_extent = (shape1->m_bottomRight.m_y - shape1->m_topLeft.m_y) / 2;

    closest.m_x = Clamp( -x_extent, x_extent, 0.0f, closest.m_x );
    closest.m_y = Clamp( -y_extent, y_extent, 0.0f, closest.m_y );

    bool inside = false;

    if(n == closest) {
        inside = true;

        if(std::abs( n.m_x ) > std::abs( n.m_y )) {
            if(closest.m_x > 0)
                closest.m_x = x_extent;
            else
                closest.m_x = -x_extent;
        } else {
            if(closest.m_y > 0)
                closest.m_y = y_extent;
            else
                closest.m_y = -y_extent;
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
    if(inside) {
        collision->normal = n * -1;
        collision->normal.normalize();
        collision->penetration = r - d;
    } else {
        collision->normal = n;
        collision->normal.normalize();
        collision->penetration = r - d;
    }
    return true;
}




inline void processTriggerCollisionRectangle_Circle(const RectangleCollider* shape1, const Transform* transform1, ColliderTrigger* trigger,
                                                    const CircleCollider* shape2, const Transform* transform2){
    if (! ServerGameConstants::kCollisionMatrix[shape1->m_CollisionLayer][shape2->m_CollisionLayer])
        return;
    if (! checkForCollisionRectangle_Circle(shape1, transform1, shape2, transform2, nullptr, true))
        return;
    trigger->m_Triggered = true;

}

inline void processTriggerCollisionRectangle_Rectangle(const RectangleCollider* shape1, const Transform* transform1, ColliderTrigger* trigger,
                                                    const RectangleCollider* shape2, const Transform* transform2){
    if (! ServerGameConstants::kCollisionMatrix[shape1->m_CollisionLayer][shape2->m_CollisionLayer])
        return;
    if (! checkForCollisionRectangle_Rectangle(shape1, transform1, shape2, transform2, nullptr, true))
        return;

    trigger->m_Triggered = true;

}

inline void processTriggerCollisionCircle_Circle(const CircleCollider* shape1, const Transform* transform1, ColliderTrigger* trigger,
                                                    const CircleCollider* shape2, const Transform* transform2){
    if (! ServerGameConstants::kCollisionMatrix[shape1->m_CollisionLayer][shape2->m_CollisionLayer])
        return;
    if (! checkForCollisionCircle_Circle(shape1, transform1, shape2, transform2, nullptr, true))
        return;
    trigger->m_Triggered = true;

}


inline void processCollisionRectangle_Circle(const RectangleCollider* shape1, RigidBody* body1, const Transform* transform1, const CircleCollider* shape2,
                                              RigidBody* body2, const Transform* transform2){
    if (! ServerGameConstants::kCollisionMatrix[shape1->m_CollisionLayer][shape2->m_CollisionLayer])
        return;
    Collision collision(*body1, *body2);
    if (checkForCollisionRectangle_Circle(shape1, transform1, shape2, transform2, &collision, false))
        resolveCollision(collision);

}


inline void processCollisionRectangle_Rectangle(const RectangleCollider* shape1, RigidBody* body1, const Transform* transform1, const RectangleCollider* shape2,
                                                             RigidBody* body2, const Transform* transform2){
    if (! ServerGameConstants::kCollisionMatrix[shape1->m_CollisionLayer][shape2->m_CollisionLayer])
        return;
    Collision collision(*body1, *body2);
    if (checkForCollisionRectangle_Rectangle(shape1, transform1, shape2, transform2, &collision, false))
        resolveCollision(collision);
}



inline void processCollisionCircle_Circle(const CircleCollider* shape1, RigidBody* body1,
                                           const Transform* transform1, const CircleCollider* shape2, RigidBody* body2, const Transform* transform2) {
    if (! ServerGameConstants::kCollisionMatrix[shape1->m_CollisionLayer][shape2->m_CollisionLayer])
        return;

    Collision collision(*body1, *body2);
    if (checkForCollisionCircle_Circle(shape1, transform1, shape2, transform2, &collision, false))
        resolveCollision(collision);
}












template <typename TSettings>
class PhysicSystem {
private:
    ComponentManager<TSettings>* m_ComponentManager;
    float m_left, m_right, m_up, m_down;

public:

    void setManager(ComponentManager<TSettings>* manager){
        m_ComponentManager = manager;
    }

    void setBoundaries(float left, float right, float up, float down){
        m_left = left;
        m_right = right;
        m_up = up;
        m_down = down;
    }


    // only if you wish to run physics as internal system, on the same thread as engine
    void run(float dt){
        runPhysicUpdate(dt);
    }

    void runPhysicUpdate(float dt) {

        std::lock_guard<std::mutex> lock (m_ComponentManager->componentsMutex);


        m_ComponentManager->template forEntitiesMatching<SystemSignature_Movable>([dt, this](RigidBody* rigidBody, Transform* transform){
            transform->m_position += rigidBody->m_velocity * dt;
            if (rigidBody->m_velocity.length() > 0.0005f) {
                rigidBody->m_velocity *= rigidBody->m_speedDecrement;
            } else {
                rigidBody->m_velocity = {0.0f, 0.0f};
            }
            if (transform->m_position.m_x > m_right)
                transform->m_position.m_x = m_right;
            if (transform->m_position.m_x < m_left)
                transform->m_position.m_x = m_left;
            if (transform->m_position.m_y > m_up)
                transform->m_position.m_y = m_up;
            if (transform->m_position.m_y < m_down)
                transform->m_position.m_y = m_down;

        });

        m_ComponentManager->template forEntitiesMatchingPairs<SystemSignature_Circle_Collider_Body, SystemSignature_Circle_Collider_Body>(processCollisionCircle_Circle);
        m_ComponentManager->template forEntitiesMatchingPairs<SystemSignature_Rectangle_Collider_Body, SystemSignature_Rectangle_Collider_Body>(processCollisionRectangle_Rectangle);
        m_ComponentManager->template forEntitiesMatchingPairs<SystemSignature_Rectangle_Collider_Body, SystemSignature_Circle_Collider_Body>(processCollisionRectangle_Circle);

        m_ComponentManager->template forEntitiesMatchingPairs<SystemSignature_TCollider_Circle, SystemSignature_Circle_Collider>(processTriggerCollisionCircle_Circle);
        m_ComponentManager->template forEntitiesMatchingPairs<SystemSignature_TCollider_Rectangle, SystemSignature_Rectangle_Collider>(processTriggerCollisionRectangle_Rectangle);
        m_ComponentManager->template forEntitiesMatchingPairs<SystemSignature_TCollider_Rectangle, SystemSignature_Circle_Collider>(processTriggerCollisionRectangle_Circle);
    }

    void start() {

        Uint32 accumulator = 0;
        Timer timer;
        timer.start();


        Uint32 frameStart = timer.getTime();
        timer.resetTime();


        while( true ) {
            if (m_ComponentManager->shouldQuit())
                return;
            accumulator += timer.getTime() - frameStart;

            frameStart = timer.getTime();

            if (accumulator > ServerGameConstants::kPhysicAccumulatorLimit)
                accumulator = ServerGameConstants::kPhysicAccumulatorLimit;

            while (accumulator > ServerGameConstants::kPhysicDeltaTime) {
                runPhysicUpdate(ServerGameConstants::kPhysicDeltaTime);
                accumulator -= ServerGameConstants::kPhysicDeltaTime;
            }
        }

    }
};


#endif //PV264_PROJECT_PHYSICENGINE_H
