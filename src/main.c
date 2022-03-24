#include <stdio.h>
#include <SDL2/SDL.h>

#include "window.h"
#include "button.h"

int manage_events(SDL_Event e) {
    switch (e.type) {
        case SDL_QUIT:
            return 0;
    }
    return 1;
}

int bubble_sort(Window *window, SDL_Rect rects[], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (rects[i].h > rects[j].h) {
                int temp = rects[i].h;
                rects[i].h = rects[j].h;
                rects[j].h = temp;
                
                SDL_RenderClear(window->renderer);
                for (int i = 0; i < N; i++) {
                    SDL_SetRenderDrawColor(window->renderer, 0x00, 0xFF, 0xFF, 0xFF);
                    SDL_RenderFillRect(window->renderer, &rects[i]);
                }
                SDL_SetRenderDrawColor(window->renderer, 0x19, 0x019, 0x19, 0xFF);
                SDL_RenderPresent(window->renderer);

            }
        }
    }
    return 0;
}

int main() {
    float const  WINDOW_WIDTH = 1080;
    float const ASPECT_RATIO  = 16.0 / 9.0;
    float const  WINDOW_HEIGHT = (int) ((float) WINDOW_WIDTH / ASPECT_RATIO);
    
    Window window;
    window_init(&window, WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Event event;
    int keep_window_open = 1;

    int N = 100;
    SDL_Rect rects[N];
    float rects_width = WINDOW_WIDTH / N;

    for (int i = 0, j = N; i < N; i++) {
        rects[i].x = i * rects_width; 
        rects[i].y = WINDOW_HEIGHT;
        rects[i].w = rects_width;
        rects[i].h = - j;
        j--;
    }


    Button button;
    button_init(&button, 100, 100, 100, -100);

    int sorted = 1;
    while (keep_window_open) {
        SDL_WaitEvent(&event);
        keep_window_open = manage_events(event);
        
        //if (sorted) {
        //    sorted = bubble_sort(&window, rects, N);
        //}

        SDL_RenderClear(window.renderer);
        button_render(&button, &window);
        for (int i = 0; i < N; i++) {
            SDL_SetRenderDrawColor(window.renderer, 0x00, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRect(window.renderer, &rects[i]);
        }

        SDL_SetRenderDrawColor(window.renderer, 0x19, 0x019, 0x19, 0xFF);
        SDL_RenderPresent(window.renderer);
    }

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.sdl_window);
    SDL_Quit();
    return 0;
}