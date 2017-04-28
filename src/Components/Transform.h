//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_TRANSFORM_H
#define PV264_PROJECT_TRANSFORM_H

#include "../Utils/Vector2.h"

struct Transform{
Vector_Float m_position;

    Transform(const Vector_Float &m_position) : m_position(m_position) {}
    Transform() = default;

};
#endif //PV264_PROJECT_TRANSFORM_H
