#include "Game.h"
#include "SDL_image.h"

#ifndef BALLJUMP_TEXTUREMANAGER_H
#define BALLJUMP_TEXTUREMANAGER_H


class TextureManager {

public:
    static SDL_Texture *LoadTexture(const char *fileName);
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};


#endif //BALLJUMP_TEXTUREMANAGER_H
