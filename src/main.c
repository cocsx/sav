#include <stdio.h>
#include <SDL2/SDL.h>

#include "../headers/window.h"
#include "../headers/button.h"
#include "../headers/sorting_algorithms.h"

int main_menu_loop(Window *window) {
    SDL_Event event;

    Button insertion_sort, shaker_sort, quick_sort, heap_sort, merge_sort, quit_button;
    button_init(&insertion_sort, "Insertion sort", 100, 10, 200, 50);
    button_init(&shaker_sort, "Shaker sort", 100, 70, 200, 50);
    button_init(&quick_sort, "Quick sort", 100, 130, 200, 50);
    button_init(&heap_sort, "Heap sort", 100, 190, 200, 50);
    button_init(&merge_sort, "Merge sort", 100, 250, 200, 50);
    button_init(&quit_button, "QUIT", 100, 400, 200, 50);

    int quit = 1;
    SDL_RenderClear(window->renderer);
    while (quit) {
        SDL_WaitEvent(&event);
        SDL_RenderClear(window->renderer);

        if (button_render(&insertion_sort, window, &event))
            return 1;
        if (button_render(&shaker_sort, window, &event))
            return 2;
        if (button_render(&quick_sort, window, &event))
            return 3; 
        if (button_render(&heap_sort, window, &event))
            return 4; 
        if (button_render(&merge_sort, window, &event))
            return 5;

        quit = 1 - button_render(&quit_button, window, &event);
        SDL_SetRenderDrawColor(window->renderer, 0x19, 0x019, 0x19, 0xFF);
        SDL_RenderPresent(window->renderer);
    }


    button_free(&insertion_sort);
    button_free(&shaker_sort);
    button_free(&quick_sort);
    button_free(&heap_sort);
    button_free(&merge_sort);
    button_free(&quit_button);

    return quit;
}

int main() {
    float const  WINDOW_WIDTH = 1280;
    float const ASPECT_RATIO  = 16.0 / 9.0;
    float const  WINDOW_HEIGHT = WINDOW_WIDTH / ASPECT_RATIO;
    int N = 600;

    Window window;
    window_init(&window, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (TTF_Init() < 0) {
        printf("[FATAL] Failed to initialize SDL2_TTF!\n");
        return -1;
    }

    int keep_window_open = 1;
    
    while (keep_window_open) {
        keep_window_open = 1;
        SDL_RenderClear(window.renderer);
        int index = main_menu_loop(&window);
        void (*fun_sort_arr[])(Datas *, Window *, int, int) = {
            insertion_sort, 
            shaker_sort, 
            quick_sort, 
            heap_sort, 
            merge_sort
        };

        if (index != 0) {
            int sorted = 1;
            SDL_Event event;

            index--;
            Datas datas;
            datas_init(&datas, N, WINDOW_WIDTH, WINDOW_HEIGHT);

            Button quit_button, main_menu;
            button_init(&quit_button, "QUIT", 100, 400, 200, 50);
            button_init(&main_menu, "MENU", 100, 300, 200, 50);

            while (keep_window_open == 1) {
                SDL_WaitEvent(&event);
                SDL_RenderClear(window.renderer);

                if (sorted) {
                    (*fun_sort_arr[index])(&datas, &window, 0, N - 1);
                    sorted = 0;
                }
                datas_render(&datas, &window);

                if (button_render(&main_menu, &window, &event)) 
                    keep_window_open = - 1;

                if(button_render(&quit_button, &window, &event))
                    keep_window_open = 0;
                
                SDL_SetRenderDrawColor(window.renderer, 0x19, 0x019, 0x19, 0xFF);
                SDL_RenderPresent(window.renderer);
            }

            button_free(&quit_button);
            button_free(&main_menu);
            datas_free(&datas);  
        } else {
            keep_window_open = 0;
        }
    }

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.sdl_window);
    SDL_Quit();
    return 0;
}
