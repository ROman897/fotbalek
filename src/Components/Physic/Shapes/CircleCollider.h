//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_CIRCLE_H
#define PV264_PROJECT_CIRCLE_H

#include "../../../Constants/ServerGameConstants.h"
#include "../../../Utils/Declarations.h"

struct CircleCollider {
  Vector_Float m_center;
  float m_radius;
  CollisionLayers m_CollisionLayer;

  CircleCollider(const Vector_Float &m_center, float m_radius,
                 CollisionLayers layer)
      : m_center(m_center), m_radius(m_radius), m_CollisionLayer(layer) {}
  CircleCollider() = default;
};

#endif // PV264_PROJECT_CIRCLE_H
