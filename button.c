#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "const.h"
#include "button.h"


Button *createButton(int x, int y, int w, int h, char type, SDL_Texture *texture) {
    Button *button = malloc(sizeof(Button));
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;
    button->type = type;
    button->texture = texture;
    button->hoveredLastFrame = 0;
    return button;
}


void loadButtons(Button **buttons, SDL_Texture **textures) {
    buttons[0] = createButton(32, 112, 64, 64, '+', textures[0]);
    buttons[1] = createButton(32, 192, 64, 64, '7', textures[1]);
    buttons[2] = createButton(32, 272, 64, 64, '4', textures[2]);
    buttons[3] = createButton(32, 352, 64, 64, '1', textures[3]);
    buttons[4] = createButton(32, 432, 64, 64, '%', textures[4]);
    buttons[5] = createButton(112, 112, 64, 64, '-', textures[5]);
    buttons[6] = createButton(112, 192, 64, 64, '8', textures[6]);
    buttons[7] = createButton(112, 272, 64, 64, '5', textures[7]);
    buttons[8] = createButton(112, 352, 64, 64, '2', textures[8]);
    buttons[9] = createButton(112, 432, 64, 64, '0', textures[9]);
    buttons[10] = createButton(192, 112, 64, 64, '*', textures[10]);
    buttons[11] = createButton(192, 192, 64, 64, '9', textures[11]);
    buttons[12] = createButton(192, 272, 64, 64, '6', textures[12]);
    buttons[13] = createButton(192, 352, 64, 64, '3', textures[13]);
    buttons[14] = createButton(192, 432, 64, 64, '.', textures[14]);
    buttons[15] = createButton(272, 112, 64, 64, '/', textures[15]);
    buttons[16] = createButton(272, 192, 64, 144, 'a', textures[16]);
    buttons[17] = createButton(272, 352, 64, 144, '=', textures[17]);
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
    SDL_Rect rect;
    if (button->type == 'a' || button->type == '=') {
        rect = (SDL_Rect){ .x = button->rect.x + 12, .y = button->rect.y + 46, .w = 40, .h = 52 };
    } else {
        rect = (SDL_Rect){ .x = button->rect.x + 16, .y = button->rect.y + 6, .w = 32, .h = 52 };
    }
    SDL_RenderCopy(renderer, button->texture, NULL, &rect);
}


void destroyButtons(Button **buttons) {
    for (int i = 0; i < NBUTTONS; i++) {
        free(buttons[i]);
    }
}
