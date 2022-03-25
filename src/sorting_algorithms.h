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

void datas_init(Datas *datas, int N, float window_width, float window_height) {
    datas->N = N;
    datas->rects = (SDL_Rect *) malloc(N * sizeof(SDL_Rect));

    float rects_width = window_width / N;
    for (int i = 0, j = N; i < N; i++, j--) {
        datas->rects[i].x = i * rects_width; 
        datas->rects[i].y = window_height;
        datas->rects[i].w = rects_width;
        datas->rects[i].h = -j;
    }
}

void datas_render(Datas* datas, Window* window) {
    for (int i = 0; i < datas->N; i++) {
        SDL_SetRenderDrawColor(window->renderer, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(window->renderer, &datas->rects[i]);
    }
}

void datas_render_when_sorting(Datas* datas, Window* window, int time) {
    SDL_RenderClear(window->renderer);
    for (int i = 0; i < datas->N; i++) {
        SDL_SetRenderDrawColor(window->renderer, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(window->renderer, &datas->rects[i]);
    }
    SDL_SetRenderDrawColor(window->renderer, 0x19, 0x019, 0x19, 0xFF);
    SDL_RenderPresent(window->renderer);
    usleep(time);
}

void swap(Datas *datas, Window *window, int num1, int num2, int time) {
   int temp = datas->rects[num1].h;
   datas->rects[num1].h = datas->rects[num2].h;
   datas->rects[num2].h = temp;
   datas_render_when_sorting(datas, window, time);
}

// =======================================================> INSERTIONSORT
void insertion_sort(Datas *datas, Window *window, int start, int end) {
    for (int i = 0; i < datas->N; i++) {
        for (int j = 0; j < datas->N; j++) {
            if (datas->rects[i].h > datas->rects[j].h) {
                swap(datas, window, i, j, 100);
            }
        }
    }
}
// INSERTIONSORT <=======================================================

// =======================================================> BUBBLESORTSORT
void bubble_sort(Datas *datas, Window *window, int start, int end) {
   int i, j;
   for (i = 0; i < datas->N; i++) { 
       for (j = 0; j < datas->N; j++) {
           if (datas->rects[j].h < datas->rects[j + 1].h){
              swap(datas, window, j, j + 1, 200);
            }
        }
    }
}
// BUBBLESORT <=======================================================

// =======================================================> QUICKSORT
int partition(Datas *datas, Window *window, int l, int h) {
    int x = datas->rects[h].h;
    int i = (l - 1);
  
    for (int j = l; j <= h - 1; j++) {
        if (datas->rects[j].h <= x) {
            i++;
            swap(datas, window, i, j, 900);
        }
    }
    swap(datas, window, i + 1, h, 900);
    return (i + 1);
}

void quick_sort(Datas *datas, Window *window, int start, int end) {
    int stack[end - start + 1];
    int top = -1;
    stack[++top] = start;
    stack[++top] = end;
  
    while (top >= 0) {
        end = stack[top--];
        start = stack[top--];

        int p = partition(datas, window, start, end);
        if (p - 1 > start) {
            stack[++top] = start;
            stack[++top] = p - 1;
        }
  
        if (p + 1 < end) {
            stack[++top] = p + 1;
            stack[++top] = end;
        }
    }
}
// QUICKSORT <=======================================================

// =======================================================> HEAPSORT
void heapify(Datas *datas, Window *window, int n, int i) {
    int largest = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2;
 
    if (l < n && datas->rects[l].h < datas->rects[largest].h) {
        largest = l;
    }
 
    if (r < n && datas->rects[r].h < datas->rects[largest].h) {
        largest = r;
    }

    if (largest != i) {
        swap(datas, window, i, largest, 1000);
        heapify(datas, window, n, largest);
    }
}
 
void heap_sort(Datas *datas, Window *window, int start, int end) {
    for (int i = end / 2 - 1; i >= 0; i--) {
        heapify(datas, window, end, i);
    }
 
    for (int i = end - 1; i > 0; i--) {
        swap(datas, window, 0, i, 1000);
        heapify(datas, window, i, 0);
    }
}
// HEAPSORT <=======================================================

// =======================================================>  MERGESORT
void merge(Datas *datas, Window *window, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
  
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = datas->rects[l + i].h;
    }
    for (j = 0; j < n2; j++) {
        R[j] = datas->rects[m + 1 + j].h;
    }
  
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] > R[j]) {
            datas->rects[k].h = L[i];
            i++;
        } else {
            datas->rects[k].h = R[j];
            j++;
        }
        datas_render_when_sorting(datas, window, 1000);
        k++;
    }
    
    while (i < n1) {
        datas->rects[k].h = L[i];
        i++; k++;
        datas_render_when_sorting(datas, window, 1000);
    }
  
    while (j < n2) {
        datas->rects[k].h = R[j];
        j++; k++;
        datas_render_when_sorting(datas, window, 1000);
    }
}
  
void merge_sort(Datas *datas, Window *window, int start, int end) {
    if (start < end) {
        int m = start+(end-start)/2;
        merge_sort(datas, window, start, m);
        merge_sort(datas, window, m + 1, end);
        merge(datas, window, start, m, end);
    }
}
// MERGESORT <========================================================
