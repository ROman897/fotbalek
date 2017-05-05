//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_CIRCLE_H
#define PV264_PROJECT_CIRCLE_H

#include "../../../Utils/declarations.h"

struct CircleCollider{
    Vector_Float m_center;
    float m_radius;

    CircleCollider(const Vector_Float &m_center, float m_radius) : m_center(m_center), m_radius(m_radius) {}
    CircleCollider() = default;
};

#endif //PV264_PROJECT_CIRCLE_H
