#include <stdio.h>
#include <SDL2/SDL.h>

#include "window.h"

int manage_events(SDL_Event e) {
    switch (e.type) {
        case SDL_QUIT:
            return 0;
    }
    return 1;
}

void render(SDL_Renderer *renderer, SDL_Rect rects[], int N) {
    for (int i = 0; i < N; i++) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, &rects[i]);
    }
    SDL_RenderPresent(renderer);
}

int main() {
    float const  WINDOW_WIDTH = 1080;
    float const ASPECT_RATIO  = 16.0 / 9.0;
    float const  WINDOW_HEIGHT = (int) ((float) WINDOW_WIDTH / ASPECT_RATIO);
    
    Window window;
    window_init(&window, WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Event event;
    int keep_window_open = 1;

    int N = 500;
    SDL_Rect rects[N];
    float rects_width = WINDOW_WIDTH / N;

    for (int i = 0, j = N; i < N; i++) {
        rects[i].x = i * rects_width; 
        rects[i].y = WINDOW_HEIGHT;
        rects[i].w = rects_width;
        rects[i].h = - j;
        j--;
    }

    int sorted = 1;
    while (keep_window_open) {
        SDL_WaitEvent(&event);
        keep_window_open = manage_events(event);
        SDL_SetRenderDrawColor(window.renderer, 0x00, 0xFF, 0xFF, 0xFF);

        if (sorted) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (rects[i].h > rects[j].h) {
                        int temp = rects[i].h;
                        rects[i].h = rects[j].h;
                        rects[j].h = temp;
                        
                        SDL_SetRenderDrawColor(window.renderer, 0x001, 0x001, 0x001, 0xFF);
                        SDL_RenderClear(window.renderer);
                        render(window.renderer, rects, N);
                    }
                }
            }
            sorted = 0;
        }

        render(window.renderer, rects, N);
    }

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.sdl_window);
    SDL_Quit();
    return 0;
}