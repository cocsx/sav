#include "../headers/window.h"

int window_init(Window *self, int window_width, int window_height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[FATAL] Failed to initialize the SDL2 library\n");
        return -1;
    }
    
    self->sdl_window = SDL_CreateWindow("SAV", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
    if (!self->sdl_window) {
        printf("[FATAL] Failed to create window\n");
        return -1;
    }

    self->renderer = SDL_CreateRenderer(self->sdl_window, -1, 0);
    if(!self->renderer) {
        printf("[FATAL] Failed to create renderer from the window\n");
        return -1;
    }
    return 0;
}
