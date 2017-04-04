//
// Created by roman on 4.4.2017.
//

#include "PhysicEngine.h"
#include "Timer.h"

void PhysicEngine::runPhysicUpdate(double dt) {
    for (auto body1 = bodies.begin(); body1 != bodies.end(); ++body1 ){
        for (auto body2 = body1 + 1; body2 != bodies.end(); ++body2){
            checkForCollision(*body1, *body2);
        }
    }

}

void PhysicEngine::run() {

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

void PhysicEngine::checkForCollision(RigidBody *body1, RigidBody *body2) {
    _checkForCollision(body1->getShape(), body2->getShape(), body1, body2);
}


// spesific collision detection for two circles
template <>
void PhysicEngine::_checkForCollision(const Circle& shape1, const Circle& shape2, RigidBody* body1, RigidBody* body2){


    // Vector from A to B
    Vector2 n = body2->getPosition() - body1->getPosition();

    double r = shape1.radius + shape2.radius;
    r *= r;

    if(n.lengthSquared() > r)
        return;

    Collision collision;
    collision.first = body1;
    collision.second = body2;


    double d = n.length();

    // If distance between circles is not zero
    if(d != 0)
    {
        // Distance is difference between radius and distance
        collision.penetration = r - d;

        // now we have to calculate vector perpendicular to vector n and normalize it
        Vector2 normal = n.getNormal();
        collision.normal = normal / d;

    }

        // Circles are on same position
    else
    {
        // this should not be really happening, but just in case when distance is 0 so we dont divide by 0
        collision.penetration = shape1.radius;
        collision.normal = Vector2( 1, 0 );
    }
    resolveCollision(collision);
}

template <>
void PhysicEngine::_checkForCollision(const Rectangle& shape1, const Rectangle& shape2, RigidBody* body1, RigidBody* body2){


    Vector2 n = body2->getPosition() - body2->getPosition();

    double a_extentX = (shape1.topLeft.x - shape1.bottomRight.x) / 2;
    double b_extentX = (shape2.topLeft.x - shape2.bottomRight.x) / 2;
    double x_overlap = a_extentX + b_extentX - std::abs( n.x );


    double a_extentY = (shape1.topLeft.y - shape1.bottomRight.y) / 2;
    double b_extentY = (shape2.topLeft.y - shape2.bottomRight.y) / 2;
    double y_overlap = a_extentY + b_extentY - std::abs( n.y );

    // this means that no collision occured
    if (x_overlap <=0 && y_overlap <= 0)
        return;

    Collision collision;
    collision.first = body1;
    collision.second = body2;

    if(x_overlap > y_overlap)
    {
        if(n.x < 0)
            collision.normal = Vector2(-1, 0);
        else
            collision.normal = Vector2( 1, 0 );
        collision.penetration = x_overlap;
    }
    else
    {
        if(n.y < 0)
            collision.normal = Vector2( 0, -1 );
        else
            collision.normal = Vector2( 0, 1 );
        collision.penetration = y_overlap;
    }

    resolveCollision(collision);
}

template <>
void PhysicEngine::_checkForCollision(const Rectangle& shape1, const Circle& shape2, RigidBody* body1, RigidBody* body2){

    Vector2 n = body2->getPosition() - body1->getPosition();
    Vector2 closest = n;
    double x_extent = (shape1.topLeft.x - shape1.bottomRight.x) / 2;
    double y_extent = (shape1.topLeft.y - shape1.bottomRight.y) / 2;

    closest.x = Clamp( -x_extent, x_extent, closest.x );
    closest.y = Clamp( -y_extent, y_extent, closest.y );

    bool inside = false;

    if(n == closest)
    {
        inside = true;

        if(std::abs( n.x ) > std::abs( n.y ))
        {
            if(closest.x > 0)
                closest.x = x_extent;
            else
                closest.x = -x_extent;
        }

        else
        {

            if(closest.y > 0)
                closest.y = y_extent;
            else
                closest.y = -y_extent;
        }
    }

    Vector2 normal = n - closest;
    double d = normal.lengthSquared();
    double r = shape2.radius;

    if(d > r * r && !inside)
        return;

    d = std::sqrt( d );

    Collision collision;
    collision.first = body1;
    collision.second = body2;
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






void PhysicEngine::resolveCollision(const Collision &collision) {
    Vector2 v = collision.second->getVelocity() - collision.first->getVelocity();

    double velAlongNormal = DotProduct( v, collision.normal);

    if(velAlongNormal > 0)
        return;

    // Calculate restitution
    double e = std::min( collision.first->getRestitution(), collision.second->getRestitution());

    // Calculate impulse scalar
    double j = -(1 + e) * velAlongNormal;
    j /= collision.first->getInverseMass() + collision.second->getInverseMass();

    // Apply impulse
    Vector2 impulse = collision.normal * j;
    //A.velocity -= 1 / A.mass * impulse
    //B.velocity += 1 / B.mass * impulse
    collision.first->applyForce(impulse * -1);
    collision.second->applyForce(impulse);

}

double PhysicEngine::Clamp(double min, double max, double val) {
    return std::abs(min - val) < std::abs(max - val) ? min : max;
}
