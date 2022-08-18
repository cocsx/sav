#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct window {
    SDL_Window *sdl_window;
    SDL_Renderer *renderer;
} Window;

int window_init(Window *self, int window_width, int window_height);

#endif // WINDOW_H
