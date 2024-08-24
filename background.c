#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include "background.h"
#include "const.h"




const char* kernelSource = 
    "__kernel void setPixels(__global uchar4* pixels, int width, int height, float time) {\n"
    "   int x = get_global_id(0);\n"
    "   int y = get_global_id(1);\n"
    "   int idx = y * width + x;\n"
    "   float cx = width / 2.0f;\n"
    "   float cy = height / 2.0f;\n"
    "   float angle = time/2.0f;\n"
    "   float s = sin(angle);\n"
    "   float c = cos(angle);\n"
    "   float nx = c * (x - cx) - s * (y - cy) + cx;\n"
    "   float ny = s * (x - cx) + c * (y - cy) + cy;\n"
    "   uchar r = (uchar)(255 * (nx / (float)width));\n"
    "   uchar g = (uchar)(255 * (ny / (float)height));\n"
    "   uchar b = (uchar)(255 * ((nx + ny) / (float)(width + height)));\n"
    "   pixels[idx] = (uchar4)(r, g, b, 255);\n"
    "}\n"
;


float max(float a, float b) {
    if (a<b)return b;
    else return a;
}


void checkError(cl_int err, const char* operation) {
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Error during operation '%s': %d\n", operation, err);
        exit(1);
    }
}


int initializeOpenCL(cl_context* context, cl_command_queue* queue, cl_program* program, cl_kernel* kernel, cl_mem* bufPixels, size_t bufferSize) {
    cl_int err;
    cl_platform_id platform;
    cl_device_id device;
    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;

    // Get platform and device information
    err = clGetPlatformIDs(1, &platform, NULL);
    checkError(err, "clGetPlatformIDs");
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    checkError(err, "clGetDeviceIDs");

    // Create OpenCL context
    *context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    checkError(err, "clCreateContext");

    // Create command queue
    *queue = clCreateCommandQueueWithProperties(*context, device, 0, &err);
    checkError(err, "clCreateCommandQueueWithProperties");

    // Create program from source
    *program = clCreateProgramWithSource(*context, 1, &kernelSource, NULL, &err);
    checkError(err, "clCreateProgramWithSource");

    // Build program
    err = clBuildProgram(*program, 1, &device, NULL, NULL, NULL);
    checkError(err, "clBuildProgram");

    // Create kernel
    *kernel = clCreateKernel(*program, "setPixels", &err);
    checkError(err, "clCreateKernel");

    // Allocate memory for pixel buffer
    *bufPixels = clCreateBuffer(*context, CL_MEM_WRITE_ONLY, bufferSize, NULL, &err);
    checkError(err, "clCreateBuffer");

    // Set kernel arguments
    err = clSetKernelArg(*kernel, 0, sizeof(cl_mem), bufPixels);
    // checkError(err, "clSetKernelArg");
    err = clSetKernelArg(*kernel, 1, sizeof(int), &width);
    checkError(err, "clSetKernelArg");
    err = clSetKernelArg(*kernel, 2, sizeof(int), &height);
    checkError(err, "clSetKernelArg");

    return 0;
}


void renderFrame(SDL_Renderer* renderer, SDL_Texture* texture, cl_command_queue queue, cl_kernel kernel, cl_mem bufPixels, size_t bufferSize, cl_uchar4* pixels, SDL_Texture* whiteTexture) {
    // Set dynamic kernel argument
    float time = SDL_GetTicks() / 1000.0f;
    cl_int err = clSetKernelArg(kernel, 3, sizeof(float), &time);
    checkError(err, "clSetKernelArg (time)");

    // Execute the kernel
    size_t globalSize[2] = { WINDOW_WIDTH, WINDOW_HEIGHT };
    err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalSize, NULL, 0, NULL, NULL);
    checkError(err, "clEnqueueNDRangeKernel");

    // Read pixel data from GPU
    err = clEnqueueReadBuffer(queue, bufPixels, CL_TRUE, 0, bufferSize, pixels, 0, NULL, NULL);
    checkError(err, "clEnqueueReadBuffer");

    // Update texture with pixel data
    SDL_UpdateTexture(texture, NULL, pixels, WINDOW_WIDTH * sizeof(cl_uchar4));

    // Render texture to screen
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_Rect rect = { .x = 16, .y = 16, .w = 336, .h = 496 };
    SDL_RenderCopy(renderer, whiteTexture, NULL, &rect);
}
