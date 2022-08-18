#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"

typedef struct button {
    SDL_Rect rect;
    char *text;
    SDL_Color active_color, inactive_color;
    SDL_Surface* message_surface;
} Button;

void button_init(Button *button, char *text, int x, int y, int w, int h);

void button_free(Button *button);

int button_is_selected(Button *button);

int mouse_is_pressed(SDL_Event *event);

int button_render(Button *button, Window *window, SDL_Event *event);

#endif // BUTTON_H
