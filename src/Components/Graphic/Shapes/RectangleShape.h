//
// Created by roman on 13.4.2017.
//

#ifndef PV264_PROJECT_RECTANGLESHAPE_H
#define PV264_PROJECT_RECTANGLESHAPE_H

#include <SDL_pixels.h>

struct RectangleShape{
    int x,y, mWidth, mHeight;
    SDL_Color m_color;
    GraphicLayers m_graphicLayer;
    bool m_enabled;

    RectangleShape() = default;
    RectangleShape(int x, int y, int mWidth, int mHeight, const SDL_Color &m_color, GraphicLayers layer, bool enabled) : x(x), y(y), mWidth(mWidth),
                                                                                      mHeight(mHeight),
                                                                                      m_color(m_color), m_graphicLayer(layer),
    m_enabled(enabled){}
};


#endif //PV264_PROJECT_RECTANGLESHAPE_H
