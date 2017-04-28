//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_GRAPHICSYSTEM_H
#define PV264_PROJECT_GRAPHICSYSTEM_H


#include "../Core/ComponentManager.h"
#include "../Components/Graphic/Shapes/CircleShape.h"
#include "../Utils/declarations.h"
#include "../Components/Transform.h"
#include "../Components/Graphic/Shapes/RectangleShape.h"
#include "../Components/Graphic/Sprite.h"
#include "../Core/EngineStructures.h"
#include "../Components/Graphic/Label.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include <map>


using FontSizeMap = std::map<int, FontSmartPtr>;

template <typename TSettings>
class GraphicSystem {

    struct SDL_Exception : public std::runtime_error {
        SDL_Exception(const std::string& message) : std::runtime_error(message){
        }
    };

    struct SDLInitializer {
        SDLInitializer()
        {
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
                throw SDL_Exception("Could not initialize SDL");
        }

        ~SDLInitializer()
        {
            SDL_Quit();
        }
    };

    /**
     * class responsible only for initializing IMG and quiting it
     */
    struct IMGInitializer {
        IMGInitializer()
        {
            int imgFlags = IMG_INIT_PNG;
            if  (! IMG_Init(imgFlags) & imgFlags)
                throw SDL_Exception("Could not initialize IMG");
        }
        ~IMGInitializer()
        {
            IMG_Quit();
        }
    };

    /**
     * class responsible for initializing TTF and quiting it
     */
    struct TTFInitializer {
        TTFInitializer()
        {
            if (TTF_Init() == -1)
                throw SDL_Exception("Could not initialize TTF");
        }
        ~TTFInitializer()
        {
            TTF_Quit();
        }
    };

    struct RendererHolder {
        RendererHolder(SDL_Window* window, int index, Uint32 flags)
        {
            renderer = SDL_CreateRenderer(window, index, flags);
            if (renderer == nullptr)
                throw SDL_Exception("Could not create rendered");
        }
        SDL_Renderer* renderer;
        ~RendererHolder()
        {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
    };

    struct SurfaceHolder {
        std::map<std::string, SurfaceSmartPtr> surfaces;
    };
    /**
     * struct holds all fonts
     */
    struct FontHolder {
        std::map<std::string, FontSizeMap> fonts;
    };
    /**
     * struct responsible for creating window and destroying it
     */
    struct WindowHolder {
        WindowHolder(std::string title, int x, int y, int w, int h, Uint32 flags)
        {
            window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
            if (window == nullptr)
                throw SDL_Exception("Could not create window");
        }
        SDL_Window* window;
        ~WindowHolder()
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    };

public:


    void draw() {
        m_componentManager->template forEntitiesMatching<SystemSignature_Circle>([this](const CircleShape& shape, const Transform& transform){
            // not yet implemented
        });
        m_componentManager->template forEntitiesMatching<SystemSignature_Rectangle>([this](const RectangleShape& shape, const Transform& transform){
            SDL_SetRenderDrawColor(this->getRenderer(), shape.m_color.r, shape.m_color.g, shape.m_color.b, shape.m_color.a);
            // draw rect with position and size of one block
            SDL_Rect fillRect = {static_cast<int>(std::round(transform.m_position.m_x + shape.x)), static_cast<int>(std::round(transform.m_position.m_y + shape.y)), shape.mWidth,
                                  shape.mHeight };
            SDL_RenderFillRect(this->getRenderer(), &fillRect);

        });


        m_componentManager->template forEntitiesMatching<SystemSignature_Sprite>([this](Sprite& sprite, const Transform& transform){
            if (! sprite.m_Texture){
                auto surface = this->getSurface(sprite.m_texturePath);
                sprite.m_Texture = TextureSmartPtr(SDL_CreateTextureFromSurface(this->getRenderer(), surface));
                if (! sprite.m_Texture) {
                    std::cout << "Unable to create texture, error: " << SDL_GetError() << std::endl;
                    // here and exception should be thrown
                    return;
                }

                sprite.m_Width = surface->w;
                sprite.m_Height = surface->h;
            }
            SDL_Rect renderQuad = { static_cast<int>(std::round(sprite.m_positionOffset.m_x + transform.m_position.m_x)),
                                    static_cast<int>(std::round(sprite.m_positionOffset.m_y + transform.m_position.m_y)),
                                    sprite.m_Width, sprite.m_Height };
            SDL_RenderCopy(this->getRenderer(), sprite.m_Texture.get(), nullptr, &renderQuad);

        });
    }

    GraphicSystem() : m_componentManager(nullptr), m_WindowHolder("MainWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_ScreenWidth, m_ScreenHeight, SDL_WINDOW_SHOWN),
                                                                       m_RendererHolder(m_WindowHolder.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC){

        // set hint render scale quality
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Cannot enable Linear texture filtering" << std::endl;
        }
        SDL_SetRenderDrawColor(m_RendererHolder.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    void setManager(ComponentManager<TSettings>* componentManager){
        m_componentManager = componentManager;
    }


    SDL_Surface* getSurface(std::string path)
    {
        // first look in map of surfaces if it already contains the surface
        auto result = m_SurfaceHolder.surfaces.find(path);
        if (result == m_SurfaceHolder.surfaces.end()) {
            // this means that surface is not present in the map of surfaces
            // so we load the surface
            SDL_Surface* loadedSurface = IMG_Load(path.c_str());
            // if surface is nullptr we return nullptr and print the error
            if (loadedSurface == nullptr) {
                std::cout << "unable to load surface at path: " << path << ", error: " << IMG_GetError() << std::endl;
                return nullptr;
            }
            // is save is on, it means we have to cache the surface for future use, so we create
            // a new smart pointer to surface and emplacfe it into the map for surfaces
            m_SurfaceHolder.surfaces.emplace(path, SurfaceSmartPtr(loadedSurface));
            // return loaded surface
            return loadedSurface;
        }
        // this means we found it, so we just return it
        return result->second.get();
    }

    TTF_Font* getFont(std::string path, int size)
    {
        auto result1 = m_FontHolder.fonts.find(path);

        // this means same font of any size hasnt been loaded
        if (result1 == m_FontHolder.fonts.end()) {
            TTF_Font* font = TTF_OpenFont(path.c_str(), size);
            // if loading was unsuccessful the just return nullptr and print error
            if (font == nullptr) {
                std::cout << "unable to load font at path: " << path << ", error: " << TTF_GetError() << std::endl;
                return nullptr;
            }
            FontSizeMap map;
            map.emplace(size, FontSmartPtr(font));
            //create a new map with the newly created surface and the emplace the map into fonts
            m_FontHolder.fonts.emplace(path, std::move(map));
            return font;
        }

        // this means that there exists map with same fonts as this
        auto result2 = result1->second.find(size);

        // this means font of desired size hasnt been loaded yet
        if (result2 == result1->second.end()) {
            // so load the font and emplace the smart pointer in the map
            TTF_Font* font = TTF_OpenFont(path.c_str(), size);
            result1->second.emplace(size, FontSmartPtr(font));
            return font;
        }

        // this means that this exact font is already loaded so just return it
        return result2->second.get();
    }

    SDL_Renderer *getRenderer() {
        return m_RendererHolder.renderer;
    }

private:
    SDLInitializer m_SdlInitializer;
    IMGInitializer m_ImgInitializer;
    TTFInitializer m_TtfInitializer;
    SurfaceHolder m_SurfaceHolder;
    FontHolder m_FontHolder;
    WindowHolder m_WindowHolder;
    RendererHolder m_RendererHolder;

    ComponentManager<TSettings>* m_componentManager;

    using SystemSignature_Circle = Signature<CircleShape, Transform>;
    using SystemSignature_Rectangle = Signature <RectangleShape, Transform>;
    using SystemSignature_Sprite = Signature <Sprite, Transform>;
    using SystemSignature_Label = Signature <Label, Transform>;
    int m_ScreenWidth;
    int m_ScreenHeight;
};


#endif //PV264_PROJECT_GRAPHICSYSTEM_H
