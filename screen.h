#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL_ttf.h>


typedef struct _Screen {
    SDL_Rect rect;
    char* display;
} Screen;

Screen *createScreen();
void updateDisplay(Screen *screen, char *c);
void renderScreen(SDL_Renderer *renderer, SDL_Texture *whiteTexture, Screen *screen, TTF_Font *font);
void destroyScreen(Screen *screen);


#endif
