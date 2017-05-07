//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_RECTANGLE_H
#define PV264_PROJECT_RECTANGLE_H


#include "../../../Utils/declarations.h"

struct RectangleCollider  {
    RectangleCollider(const Vector_Float &topLeft, const Vector_Float &bottomRight, CollisionLayers layer) : m_topLeft(topLeft),
                                                                                          m_bottomRight(
                                                                                                  bottomRight),
    m_CollisionLayer(layer){}

    RectangleCollider() = default;

    RectangleCollider(const Vector_Float &bottomRight, CollisionLayers layer) : m_topLeft({0,0}), m_bottomRight(bottomRight),
    m_CollisionLayer(layer){}

    Vector_Float m_topLeft;
    Vector_Float m_bottomRight;
    CollisionLayers m_CollisionLayer;

};


#endif //PV264_PROJECT_RECTANGLE_H
