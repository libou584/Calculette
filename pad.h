#ifndef PAD_H
#define PAD_H

#include "screen.h"

void displayPad(SDL_Renderer* renderer, SDL_Texture* whiteTexture, Screen* screen, Button **buttons, Mix_Chunk** sounds, TTF_Font* font);

#endif
