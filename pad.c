#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "button.h"
#include "screen.h"




void displayPad(SDL_Renderer* renderer, SDL_Texture* whiteTexture, Screen* screen, Button **buttons, Mix_Chunk** sounds, TTF_Font* font) {
    renderScreen(renderer, whiteTexture, screen, font);
    for (int i = 0; i < NBUTTONS; i++) {
        drawButton(renderer, whiteTexture, buttons[i], sounds);
    }
}
