#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "background.h"
#include "const.h"
#include "button.h"
#include "pad.h"
#include "sound.h"
#include "screen.h"
#include "texture.h"





int main() {
    int SCREEN_WIDTH = 1920;
    int SCREEN_HEIGHT = 1080;
    SDL_Window* window = SDL_CreateWindow("Calculette", SCREEN_WIDTH - WINDOW_WIDTH, SCREEN_HEIGHT - WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!window || !renderer) {
        fprintf(stderr, "Could not create SDL2 window or renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    TTF_Init();
	TTF_Font *font = TTF_OpenFont("asset/fonts/futura.ttf", 500);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0) {
    	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(-1);
    }
    Mix_Chunk *sounds[NSOUNDS];
	loadSounds(sounds);

    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_mem bufPixels;
    size_t bufferSize = WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(cl_uchar4);
    cl_uchar4* pixels = (cl_uchar4*)malloc(bufferSize);

    if (initializeOpenCL(&context, &queue, &program, &kernel, &bufPixels, bufferSize) != 0) {
        free(pixels);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture* bgTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!bgTexture) {
        fprintf(stderr, "Could not create SDL2 texture: %s\n", SDL_GetError());
        free(pixels);
        clReleaseMemObject(bufPixels);
        clReleaseKernel(kernel);
        clReleaseProgram(program);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture *textures[NTEXTURES];
	loadTextures(renderer, textures, font);

    Button *buttons[NBUTTONS];
    loadButtons(buttons, textures);
    Screen* screen = createScreen();

    int running = 1;
    while (running) {
        Uint32 startTime = SDL_GetTicks();
        char res;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                res = buttonClicked(buttons, event.button.x, event.button.y, sounds);
                updateDisplay(screen, res);
            }
        }

        renderFrame(renderer, bgTexture, queue, kernel, bufPixels, bufferSize, pixels, textures[18]);
        displayPad(renderer, textures[18], screen, buttons, sounds, font);
        SDL_RenderPresent(renderer);

        Uint32 endTime = SDL_GetTicks();
        Uint32 elapsedMS = endTime - startTime;
        SDL_Delay(max((1000*DT - elapsedMS)/1.0f, 0));
    }

    free(pixels);
    clReleaseMemObject(bufPixels);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    destroyScreen(screen);
    destroyButtons(buttons);
    destroyTextures(textures);
    destroySounds(sounds);
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
