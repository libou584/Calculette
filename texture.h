#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL_image.h>

void loadTextures(SDL_Renderer *renderer, SDL_Texture **textures, TTF_Font *font);
void destroyTextures(SDL_Texture **textures);

#endif
