#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *texture) {
    SDL_Surface *tmpSurface = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}

void TextureManager::Rotate(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {

    SDL_Point center{src.w/2, src.h/2};

    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 90.0f, &center, flip);
}
