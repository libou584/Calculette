#ifndef BUTTON_H
#define BUTTON_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "const.h"


typedef struct _Button {
    SDL_Rect rect;
    char type;
    SDL_Texture *texture;
    int hoveredLastFrame;
} Button;


Button *createButton(int x, int y, int w, int h, char type, SDL_Texture *texture);
void loadButtons(Button**, SDL_Texture**);
char buttonClicked(Button**, int x, int y, Mix_Chunk**);
int buttonInteract(Button*, int x, int y);
void drawButton(SDL_Renderer*, SDL_Texture*, Button*, Mix_Chunk**);
void destroyButtons(Button**);


#endif
