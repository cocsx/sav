#pragma once
#include <SDL2/SDL.h>

#include "window.h"

typedef struct button {
    SDL_Rect rect;
    int ar, ag, ab, dr, dg, db;
} Button;

void button_init(Button *button, int x, int y, int w, int h) {
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;

    button->ar = 0x00;
    button->ag = 0x00;
    button->ab = 0xFF;

    button->dr = 0xFF;
    button->dg = 0x00;
    button->db = 0x00;
}

void button_init_colors(Button *button, int x, int y, int w, int h, int ar, int ag, int ab, int dr, int dg, int db) {
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;

    button->ar = ar;
    button->ag = ag;
    button->ab = ab;

    button->dr = dr;
    button->dg = dg;
    button->db = db;
}

int button_is_selected(Button *button, Window *window) {
    SDL_PumpEvents();
    int x, y;
    SDL_GetMouseState(&x, &y);

    if ( x >= button->rect.x && x <= button->rect.x + button->rect.w && y <= button->rect.y && y >= button->rect.y + button->rect.h)
         return 1;
    return 0;
}

void button_render(Button *button, Window *window) {
    if (button_is_selected(button,window)) {
        SDL_SetRenderDrawColor(window->renderer, button->ar, button->ag, button->ab, 0xFF);
    } else {
        SDL_SetRenderDrawColor(window->renderer, button->dr, button->dg, button->db, 0xFF);
    }
    SDL_RenderFillRect(window->renderer, &button->rect);
    SDL_RenderPresent(window->renderer);
}