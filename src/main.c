#include <stdio.h>
#include <SDL2/SDL.h>

#include "window.h"
#include "button.h"
#include "sorting_algorithms.h"

int manage_events(SDL_Event e) {
    switch (e.type) {
        case SDL_QUIT:
            return 0;
    }
    return 1;
}

int main_menu_loop(Window *window) {
    SDL_Event event;
    Button merge_sort;
    button_init(&merge_sort, "merge_sort", 100, 200, 300, -50);

    int quit = 1;
    int keep_window_open = 1;
    while (keep_window_open && quit) {
        SDL_WaitEvent(&event);

        keep_window_open = button_render(&merge_sort, window, &event);
        quit = manage_events(event);

        SDL_SetRenderDrawColor(window->renderer, 0x19, 0x019, 0x19, 0xFF);
        SDL_RenderPresent(window->renderer);
    }
    return quit;
}

void game_loop(Window *window) {
    int sorted = 1;
    SDL_Event event;
    int keep_window_open = 1;

    int N = 400; 
    Datas datas;
    datas_init(&datas, N, 1080.0, (1080.0 / (16.0 / 9.0)));

    while (keep_window_open) {
        SDL_WaitEvent(&event);
        keep_window_open = manage_events(event);
        
        SDL_RenderClear(window->renderer);

        if (sorted) {
            sorted = sort_datas(&datas, window, HEAP);
        }
        datas_render(&datas, window);

        SDL_SetRenderDrawColor(window->renderer, 0x19, 0x019, 0x19, 0xFF);
        SDL_RenderPresent(window->renderer);
    }
}

int main() {
    float const  WINDOW_WIDTH = 1080;
    float const ASPECT_RATIO  = 16.0 / 9.0;
    float const  WINDOW_HEIGHT = WINDOW_WIDTH / ASPECT_RATIO;
    
    Window window;
    window_init(&window, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    int quit = main_menu_loop(&window);
    if (quit) {
        game_loop(&window);
    }

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.sdl_window);
    SDL_Quit();
    return 0;
}