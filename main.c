#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "background.h"


int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;
float DT = 1.0f/60.0f;


int main() {
    SDL_Window* window = SDL_CreateWindow("OpenCL SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!window || !renderer) {
        fprintf(stderr, "Could not create SDL2 window or renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_mem bufPixels;
    size_t bufferSize = WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(cl_uchar4);
    cl_uchar4* pixels = (cl_uchar4*)malloc(bufferSize);

    if (initializeOpenCL(&context, &queue, &program, &kernel, &bufPixels, bufferSize, WINDOW_WIDTH, WINDOW_HEIGHT) != 0) {
        free(pixels);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!texture) {
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

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        renderFrame(renderer, texture, queue, kernel, bufPixels, bufferSize, pixels, WINDOW_WIDTH, WINDOW_HEIGHT, DT);
    }
    
    free(pixels);
    clReleaseMemObject(bufPixels);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}