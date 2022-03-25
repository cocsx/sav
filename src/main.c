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

    Button insertion_sort, bubble_sort, quick_sort, heap_sort, merge_sort;
    button_init(&insertion_sort, "Insertion sort", 100, 10, 200, 50);
    button_init(&bubble_sort, "Bubble sort", 100, 70, 200, 50);
    button_init(&quick_sort, "Quick sort", 100, 130, 200, 50);
    button_init(&heap_sort, "Heap sort", 100, 190, 200, 50);
    button_init(&merge_sort, "Merge sort", 100, 250, 200, 50);

    int quit = 1;
    while (quit) {
        SDL_WaitEvent(&event);

        if (button_render(&insertion_sort, window, &event))
            return 1;
        if (button_render(&bubble_sort, window, &event))
            return 2;
        if (button_render(&quick_sort, window, &event))
            return 3; 
        if (button_render(&heap_sort, window, &event))
            return 4; 
        if (button_render(&merge_sort, window, &event))
            return 5;

        quit = manage_events(event);

        SDL_SetRenderDrawColor(window->renderer, 0x19, 0x019, 0x19, 0xFF);
        SDL_RenderPresent(window->renderer);
    }
    return quit;
}

int main() {
    float const  WINDOW_WIDTH = 1080;
    float const ASPECT_RATIO  = 16.0 / 9.0;
    float const  WINDOW_HEIGHT = WINDOW_WIDTH / ASPECT_RATIO;
    
    Window window;
    window_init(&window, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    int index = main_menu_loop(&window);
    void (*fun_sort_arr[])(Datas *, Window *, int, int) = {
        insertion_sort, 
        bubble_sort, 
        quick_sort, 
        heap_sort, 
        merge_sort
    };

    if (index != 0) {
        int sorted = 1;
        SDL_Event event;
        int keep_window_open = 1;
        
        index--;
        int N = 100; 
        Datas datas;
        datas_init(&datas, N, WINDOW_WIDTH, WINDOW_HEIGHT);
        while (keep_window_open) {
            SDL_WaitEvent(&event);
            keep_window_open = manage_events(event);

            SDL_RenderClear(window.renderer);

            if (sorted) {
                (*fun_sort_arr[index])(&datas, &window, 0, N - 1);
                sorted = 0;
            }
            datas_render(&datas, &window);

            SDL_SetRenderDrawColor(window.renderer, 0x19, 0x019, 0x19, 0xFF);
        }
    }

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.sdl_window);
    SDL_Quit();
    return 0;
}