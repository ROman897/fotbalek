//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_SPRITE_H
#define PV264_PROJECT_SPRITE_H

#include "../../Core/EngineStructures.hpp"

struct Sprite{
    int m_Width;
    int m_Height;
    Vector_Int m_positionOffset;
    std::string m_texturePath;
    TextureSmartPtr m_Texture;
};

#endif //PV264_PROJECT_SPRITE_H
