//
// Created by roman on 16.4.2017.
//

#ifndef PV264_PROJECT_LABEL_H
#define PV264_PROJECT_LABEL_H

#include "../../Core/EngineStructures.h"
#include "../../Utils/Vector2.h"

struct Label{
    int m_Width;
    int m_Height;
    Vector_Float m_positionOffset;
    TextureSmartPtr m_Texture;
    std::string m_text;
    std::string m_fontPath;
    SDL_Color m_fontColor;
    int m_size;
    GraphicLayers m_graphicLayer;
    bool m_Enabled;
    bool m_ChangedText;

    Label(const Vector_Float &m_positionOffset, const std::string &m_text, const std::string &m_fontPath,
          const SDL_Color &m_fontColor, int m_size, GraphicLayers layer, bool enabled) : m_positionOffset(m_positionOffset), m_text(m_text),
                                                                    m_fontPath(m_fontPath), m_fontColor(m_fontColor),
                                                                    m_size(m_size), m_graphicLayer(layer), m_Enabled(enabled),
    m_ChangedText(false) {}

    Label(const Vector_Float &m_positionOffset, const std::string &m_fontPath, const SDL_Color &m_fontColor, int m_size,
          GraphicLayers m_graphicLayer, bool enabled) : m_positionOffset(m_positionOffset), m_fontPath(m_fontPath),
                                                        m_fontColor(m_fontColor), m_size(m_size),
                                                        m_graphicLayer(m_graphicLayer), m_Enabled(enabled),
                                                        m_ChangedText(false){}

    Label() = default;
};
#endif //PV264_PROJECT_LABEL_H
