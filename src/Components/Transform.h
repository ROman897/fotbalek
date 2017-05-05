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

    bool operator==(const Transform &rhs) const {
        return m_position == rhs.m_position;
    }

    bool operator!=(const Transform &rhs) const {
        return !(rhs == *this);
    }

    Transform&operator=(const Transform& rhs){
        m_position = rhs.m_position;
        return *this;
    }
};
#endif //PV264_PROJECT_TRANSFORM_H
