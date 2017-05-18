//
// Created by roman on 10.2.2017.
//

#ifndef TETRIS_ENGINESTRUCTURES_H
#define TETRIS_ENGINESTRUCTURES_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

/**
 * this struct defines dealloc function for each of the smart pointer wrappers
 * provided below
 * so they can dealloc themselves using right function chosen by SDL_Deleter
 * base on type of argument it gets
 */
struct SDL_Deleter {
  void operator()(SDL_Surface *ptr) {
    if (ptr)
      SDL_FreeSurface(ptr);
  }
  void operator()(SDL_Texture *ptr) {
    if (ptr)
      SDL_DestroyTexture(ptr);
  }
  void operator()(TTF_Font *ptr) {
    if (ptr)
      TTF_CloseFont(ptr);
  }
};

// declare typedefs for smart pointer wrappers
using SurfaceSmartPtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
using TextureSmartPtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
using FontSmartPtr = std::unique_ptr<TTF_Font, SDL_Deleter>;

#endif // TETRIS_ENGINESTRUCTURES_H