#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "const.h"
#include "screen.h"


Screen* createScreen() {
    Screen *screen = malloc(sizeof(Screen));
    screen->rect.x = 32;
    screen->rect.y = 32;
    screen->rect.w = 304;
    screen->rect.h = 64;
    screen->display = malloc(256);
    screen->display[0] = '\0';
    return screen;
}


void updateDisplay(Screen *screen, char c) {
    if (c == 'a') {
        screen->display[0] = '\0';
        return;
    } else if (c != 'n') {
        size_t len = strlen(screen->display);
        screen->display[len] = c;
        screen->display[len + 1] = '\0';
    }
}


void renderScreen(SDL_Renderer *renderer, SDL_Texture *whiteTexture, Screen *screen, TTF_Font *font) {
    SDL_RenderCopy(renderer, whiteTexture, NULL, &screen->rect);
    int len = strlen(screen->display);
    if (len != 0) {
        SDL_Surface *surface = TTF_RenderText_Solid(font, screen->display, (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
        if (surface == NULL) {
            printf("Error creating surface: %s\n", TTF_GetError());
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            printf("Error creating texture: %s\n", SDL_GetError());
        }
        SDL_Rect dstRect = { .x = 32, .y = 32, .w = 304, .h = 64 };
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}


void destroyScreen(Screen *screen) {
    free(screen->display);
    free(screen);
}
