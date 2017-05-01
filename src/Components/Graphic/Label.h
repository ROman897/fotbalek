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
    bool enabled;

};
#endif //PV264_PROJECT_LABEL_H
