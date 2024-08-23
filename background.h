#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <CL/cl.h>
#include <SDL2/SDL.h>


// void checkError(cl_int err, const char* operation);
int initializeOpenCL(cl_context* context, cl_command_queue* queue, cl_program* program, cl_kernel* kernel, cl_mem* bufPixels, size_t bufferSize, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void renderFrame(SDL_Renderer* renderer, SDL_Texture* texture, cl_command_queue queue, cl_kernel kernel, cl_mem bufPixels, size_t bufferSize, cl_uchar4* pixels, int WINDOW_WIDTH, int WINDOW_HEIGHT, float DT);



#endif