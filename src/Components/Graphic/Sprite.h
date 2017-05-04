//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_SPRITE_H
#define PV264_PROJECT_SPRITE_H

#include "../../Core/EngineStructures.h"
#include "../../Constants/ClientGameConstants.h"

struct Sprite{
    int m_Width;
    int m_Height;
    Vector_Float m_positionOffset;
    std::string m_texturePath;
    TextureSmartPtr m_Texture;
    bool enabled;
    GraphicLayers m_graphicLayer;

    Sprite(const Vector_Float &m_positionOffset, const std::string &m_texturePath, GraphicLayers layer,bool enabled) : m_positionOffset(
            m_positionOffset), m_texturePath(m_texturePath), m_graphicLayer(layer), enabled(enabled) {}
    Sprite() = default;
};

#endif //PV264_PROJECT_SPRITE_H
