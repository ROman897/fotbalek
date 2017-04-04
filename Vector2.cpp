//
// Created by roman on 4.4.2017.
//

#include "Vector2.h"

Vector2::Vector2(double x, double y) : x(x), y(y) {}

Vector2::Vector2() : x(0), y(0) {}

Vector2& Vector2::add(const Vector2 &vec) {
    x += vec.x;
    y+=vec.y;
    return *this;
}

Vector2& Vector2::substract(const Vector2 &vec) {
    x -= vec.x;
    y -=vec.y;
    return *this;
}

double Vector2::lengthSquared() {
    return x*x + y*y;
}

double Vector2::length() {
    return std::sqrt(x*x + y*y);
}

Vector2& Vector2::substract(double divider) {
    x /= divider;
    y /= divider;
    return *this;
}

Vector2 Vector2::getNormal() {
    return Vector2(-y,x);
}

bool Vector2::operator==(const Vector2 &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Vector2::operator!=(const Vector2 &rhs) const {
    return !(rhs == *this);
}

Vector2 &Vector2::multiply(double multiplier) {
    x += multiplier;
    y += multiplier;
    return *this;
}
