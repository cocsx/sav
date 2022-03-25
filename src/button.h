#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"

typedef struct button {
    SDL_Rect rect;
    char *text;
    SDL_Color active_color, inactive_color;
} Button;

void button_init_colors(Button *button, char *text, int x, int y, int w, int h, SDL_Color active_color, SDL_Color inactive_color) {
    button->rect.x         = x;
    button->rect.y         = y;
    button->rect.w         = w;
    button->rect.h         = h;

    button->active_color   = active_color;
    button->inactive_color = inactive_color;
    button->text           = text;
}

void button_init(Button *button, char *text, int x, int y, int w, int h) {
    SDL_Color active_color   = (SDL_Color) { .r = 0x00, .g = 0xFF, .b = 0x00, .a = 0xFF};
    SDL_Color inactive_color = (SDL_Color) { .r = 0xFF, .g = 0x00, .b = 0x00, .a = 0xFF};
    button_init_colors(
        button, 
        text,  
        x, y, 
        w, h, 
        active_color,
        inactive_color 
        );
}

int button_is_selected(Button *button) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if ( x >= button->rect.x && x <= button->rect.x + button->rect.w && y <= button->rect.y && y >= button->rect.y + button->rect.h)
         return 1;
    return 0;
}

int mouse_is_pressed(SDL_Event *event) {
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            return 1;
    }
    return 0;
}

int button_render(Button *button, Window *window, SDL_Event *event) {
    int check = button_is_selected(button) && mouse_is_pressed(event);
    if (button_is_selected(button)) {
        SDL_SetRenderDrawColor(
            window->renderer, 
            button->active_color.r, 
            button->active_color.g, 
            button->active_color.b, 
            button->active_color.a);
    } else {
        SDL_SetRenderDrawColor(
            window->renderer, 
            button->inactive_color.r, 
            button->inactive_color.g, 
            button->inactive_color.b, 
            button->inactive_color.a);
    }
    TTF_Font *font        = TTF_OpenFont("Bullpen3D.ttf", 10);
    if (font == NULL){
        printf("[ERROR] Unable to load font: %s\n", TTF_GetError());
    }
    SDL_Surface* surface_message = TTF_RenderText_Solid(font, button->text, (SDL_Color) {0xFF, 0xFF, 0xFF, 0xFF}); 
    SDL_Texture* texture_message = SDL_CreateTextureFromSurface(window->renderer, surface_message);
    SDL_RenderCopy(window->renderer, texture_message, NULL, &button->rect);
    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(texture_message);
    TTF_CloseFont(font);
    
    SDL_RenderFillRect(window->renderer, &button->rect);
    SDL_RenderPresent(window->renderer);
    return 1 - check;
}