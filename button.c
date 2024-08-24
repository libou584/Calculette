#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "const.h"
#include "button.h"


Button *createButton(int x, int y, int w, int h, char type) {
    Button *button = malloc(sizeof(Button));
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;
    button->type = type;
    button->hoveredLastFrame = 0;
    return button;
}


void loadButtons(Button **buttons) {
    buttons[0] = createButton(32, 112, 64, 64, '+');
}


int buttonInteract(Button *button, int x, int y) {
    if (x >= button->rect.x && x <= button->rect.x + button->rect.w && y >= button->rect.y && y <= button->rect.y + button->rect.h) {
        return 1;
    }
    return 0;
}


char buttonClicked(Button **buttons, int x, int y, Mix_Chunk **sounds) { // called by menuInteract only on click
    for (int i = 0; i < NBUTTONS; i++) {
        if (buttonInteract(buttons[i], x, y)){
            Mix_PlayChannel(-1, sounds[1], 0);
            return buttons[i]->type;
        }
    }
    return 'n';
}


void drawButton(SDL_Renderer *renderer, SDL_Texture* whiteTexture, Button *button, Mix_Chunk **sounds) { // called every frame
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (buttonInteract(button, x, y)) {
        SDL_RenderCopy(renderer, whiteTexture, NULL, &button->rect);
        if (!button->hoveredLastFrame) {
            Mix_PlayChannel(-1, sounds[0], 0);
            button->hoveredLastFrame = 1;
        }
    } else {
        button->hoveredLastFrame = 0;
    }
    SDL_RenderCopy(renderer, whiteTexture, NULL, &button->rect);
}


void destroyButtons(Button **buttons) {
    for (int i = 0; i < NBUTTONS; i++) {
        free(buttons[i]);
    }
}
