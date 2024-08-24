#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "const.h"



void loadSounds(Mix_Chunk **sounds) {
    sounds[0] = Mix_LoadWAV("./asset/sounds/hover.wav");
    Mix_VolumeChunk(sounds[0], MIX_MAX_VOLUME/4);
    sounds[1] = Mix_LoadWAV("./asset/sounds/click.wav");
}


void destroySounds(Mix_Chunk **sounds) {
    for (int i = 0; i < NSOUNDS; i++) {
        Mix_FreeChunk(sounds[i]);
    }
}
