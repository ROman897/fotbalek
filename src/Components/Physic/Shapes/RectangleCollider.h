//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_RECTANGLE_H
#define PV264_PROJECT_RECTANGLE_H


#include "../../../Utils/declarations.h"

struct RectangleCollider  {
    RectangleCollider(const Vector_Float &m_topLeft, const Vector_Float &m_bottomRight) : m_topLeft(m_topLeft),
                                                                                          m_bottomRight(
                                                                                                  m_bottomRight) {}
    RectangleCollider() = default;

    Vector_Float m_topLeft;
    Vector_Float m_bottomRight;
    //bool m_isTrigger;

};


#endif //PV264_PROJECT_RECTANGLE_H
