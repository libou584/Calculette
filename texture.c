#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"
#include "const.h"


void loadTextures(SDL_Renderer *renderer, SDL_Texture **textures, TTF_Font *font){

    SDL_Surface *plusSurface = TTF_RenderText_Solid(font, "+", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *sevenSurface = TTF_RenderText_Solid(font, "7", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *fourSurface = TTF_RenderText_Solid(font, "4", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *oneSurface = TTF_RenderText_Solid(font, "1", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *modSurface = TTF_RenderText_Solid(font, "%", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *minusSurface = TTF_RenderText_Solid(font, "-", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *eightSurface = TTF_RenderText_Solid(font, "8", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *fiveSurface = TTF_RenderText_Solid(font, "5", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *twoSurface = TTF_RenderText_Solid(font, "2", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *zeroSurface = TTF_RenderText_Solid(font, "0", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *timeSurface = TTF_RenderText_Solid(font, "x", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *nineSurface = TTF_RenderText_Solid(font, "9", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *sixSurface = TTF_RenderText_Solid(font, "6", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *threeSurface = TTF_RenderText_Solid(font, "3", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *dotSurface = TTF_RenderText_Solid(font, ".", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *divSurface = TTF_RenderText_Solid(font, "/", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *acSurface = TTF_RenderText_Solid(font, "AC", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface *equalSurface = TTF_RenderText_Solid(font, "=", (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255});
    SDL_Surface* whiteSurface = SDL_CreateRGBSurface(0, 16, 16, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(whiteSurface, NULL, SDL_MapRGBA(whiteSurface->format, 200, 200, 200, 120));

    textures[0] = SDL_CreateTextureFromSurface(renderer, plusSurface);
    textures[1] = SDL_CreateTextureFromSurface(renderer, sevenSurface);
    textures[2] = SDL_CreateTextureFromSurface(renderer, fourSurface);
    textures[3] = SDL_CreateTextureFromSurface(renderer, oneSurface);
    textures[4] = SDL_CreateTextureFromSurface(renderer, modSurface);
    textures[5] = SDL_CreateTextureFromSurface(renderer, minusSurface);
    textures[6] = SDL_CreateTextureFromSurface(renderer, eightSurface);
    textures[7] = SDL_CreateTextureFromSurface(renderer, fiveSurface);
    textures[8] = SDL_CreateTextureFromSurface(renderer, twoSurface);
    textures[9] = SDL_CreateTextureFromSurface(renderer, zeroSurface);
    textures[10] = SDL_CreateTextureFromSurface(renderer, timeSurface);
    textures[11] = SDL_CreateTextureFromSurface(renderer, nineSurface);
    textures[12] = SDL_CreateTextureFromSurface(renderer, sixSurface);
    textures[13] = SDL_CreateTextureFromSurface(renderer, threeSurface);
    textures[14] = SDL_CreateTextureFromSurface(renderer, dotSurface);
    textures[15] = SDL_CreateTextureFromSurface(renderer, divSurface);
    textures[16] = SDL_CreateTextureFromSurface(renderer, acSurface);
    textures[17] = SDL_CreateTextureFromSurface(renderer, equalSurface);
    textures[18] = SDL_CreateTextureFromSurface(renderer, whiteSurface);

    SDL_FreeSurface(plusSurface);
    SDL_FreeSurface(sevenSurface);
    SDL_FreeSurface(fourSurface);
    SDL_FreeSurface(oneSurface);
    SDL_FreeSurface(modSurface);
    SDL_FreeSurface(minusSurface);
    SDL_FreeSurface(eightSurface);
    SDL_FreeSurface(fiveSurface);
    SDL_FreeSurface(twoSurface);
    SDL_FreeSurface(zeroSurface);
    SDL_FreeSurface(timeSurface);
    SDL_FreeSurface(nineSurface);
    SDL_FreeSurface(sixSurface);
    SDL_FreeSurface(threeSurface);
    SDL_FreeSurface(dotSurface);
    SDL_FreeSurface(divSurface);
    SDL_FreeSurface(acSurface);
    SDL_FreeSurface(equalSurface);
    SDL_FreeSurface(whiteSurface);
}


void destroyTextures(SDL_Texture **textures){
    for (int i = 0; i < NTEXTURES; i++) {
        SDL_DestroyTexture(textures[i]);
    }
}
