//
// Created by roman on 4.4.2017.
//

#ifndef PV264_PROJECT_RECTANGLE_H
#define PV264_PROJECT_RECTANGLE_H


#include "../../../Utils/declarations.h"

struct RectangleCollider  {
    Vector_Int m_topLeft;
    Vector_Int m_bottomRight;
    bool m_isTrigger;

};


#endif //PV264_PROJECT_RECTANGLE_H
