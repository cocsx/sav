#pragma once

#include <SDL2/SDL.h>
#include <unistd.h>

#include "window.h"

typedef struct datas {
    int N;
    SDL_Rect *rects;
} Datas;

typedef enum SortingAlgorithm {
    INSERTION,
    BUBBLE,
    QUICK,
    HEAP,
    MERGE
} SortingAlgorithm;

void datas_init(Datas *datas, int N, float window_width, float window_height);

void datas_free(Datas *datas);

void datas_render(Datas* datas, Window* window);

void datas_render_when_sorting(Datas* datas, Window* window, int time, int data1, int data2);

void swap(Datas *datas, Window *window, int i, int j, int time);

void insertion_sort(Datas *datas, Window *window, int start, int end);

void shaker_sort(Datas *datas, Window *window, int start, int end);

int partition (Datas *datas, Window *window, int start, int end);

void quick_sort(Datas *datas, Window *window, int start, int end);

void heapify(Datas *datas, Window *window, int n, int i);
 
void heap_sort(Datas *datas, Window *window, int start, int end);

void merge(Datas *datas, Window *window, int l, int m, int r);
  
void merge_sort(Datas *datas, Window *window, int start, int end);
