//
// Created by roman on 2.5.2017.
//

#ifndef PV264_PROJECT_COLLIDERTRIGGER_H
#define PV264_PROJECT_COLLIDERTRIGGER_H

#include <vector>
#include <functional>

class ColliderTrigger{
    std::vector<std::function<void(void)>> m_callbacks;
};

#endif //PV264_PROJECT_COLLIDERTRIGGER_H
