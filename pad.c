#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "button.h"


// void displayPad(SDL_Renderer* renderer, SDL_Texture* whiteTexture, Button **buttons) {
//     SDL_Rect dstRect = { .x = 32, .y = 32, .w = 304, .h = 64 };
//     SDL_RenderCopy(renderer, whiteTexture, NULL, &dstRect);
//     for (int i = 0; i < NBUTTONS; i++) {
//         SDL_RenderCopy(renderer, whiteTexture, NULL, &buttons[i]->rect);
//     }
// }


void displayPad(SDL_Renderer* renderer, SDL_Texture* whiteTexture, Button **buttons, Mix_Chunk** sounds) {
    // displayPad(renderer, whiteTexture, buttons);
    SDL_Rect dstRect = { .x = 32, .y = 32, .w = 304, .h = 64 };
    SDL_RenderCopy(renderer, whiteTexture, NULL, &dstRect);
    for (int i = 0; i < NBUTTONS; i++) {
        drawButton(renderer, whiteTexture, buttons[i], sounds);
    }
}
