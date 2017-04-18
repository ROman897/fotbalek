//
// Created by roman on 9.4.2017.
//

#ifndef PV264_PROJECT_GAMEOBJECT_H
#define PV264_PROJECT_GAMEOBJECT_H


#include <vector>
#include <memory>

#include "../Utils/declarations.h"

template <typename TSettings>
struct GameObject {

public:

    bool m_alive;
    using Bitset = typename TSettings::Bitset;

    Id m_id;
    Bitset m_bitset;

};


#endif //PV264_PROJECT_GAMEOBJECT_H
