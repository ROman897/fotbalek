//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_VECTOR2_H
#define PV264_PROJECT_VECTOR2_H
#include <cmath>


struct Vector2 {
    double x,y;
public:
    Vector2(double x, double y);
    Vector2();

    friend Vector2 operator+ (Vector2 lhs, const Vector2& rhs){
        return lhs.add(rhs);
    }

    friend Vector2& operator+= (Vector2& lhs, const Vector2& rhs){
        return lhs.add(rhs);
    }

    friend Vector2 operator- (Vector2 lhs, const Vector2& rhs){
        return lhs.substract(rhs);
    }

    friend Vector2& operator-= (Vector2& lhs, const Vector2& rhs){
        return lhs.substract(rhs);
    }

    friend Vector2 operator/ (Vector2 lhs, float rhs){
        return lhs.substract(rhs);
    }

    friend Vector2 operator/= (Vector2& lhs, float rhs){
        return lhs.substract(rhs);
    }

    friend Vector2 operator* (Vector2 lhs, float rhs){
        return lhs.multiply(rhs);
    }

    friend double DotProduct(Vector2 lhs, Vector2 rhs){
        return lhs.x * rhs.x + rhs.x * rhs.y;
    }

    bool operator==(const Vector2 &rhs) const;

    bool operator!=(const Vector2 &rhs) const;

    double lengthSquared();
    double length();

    Vector2 getNormal();

private:
    Vector2& add(const Vector2& vec);
    Vector2& substract(const Vector2& vec);
    Vector2& substract(double divider);
    Vector2& multiply(double multiplier);
};


#endif //PV264_PROJECT_VECTOR2_H
