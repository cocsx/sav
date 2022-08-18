#include "../headers/sorting_algorithms.h"

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

void datas_render_when_sorting(Datas* datas, Window* window, int time, int data1, int data2) {
    SDL_RenderClear(window->renderer);
    for (int i = 0; i < datas->N; i++) {
        if (i == data1 || i == data2) {
            SDL_SetRenderDrawColor(window->renderer, 0xFF, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(window->renderer, &datas->rects[i]);
        } else {
            SDL_SetRenderDrawColor(window->renderer, 0x00, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRect(window->renderer, &datas->rects[i]);
        }
    }
    SDL_SetRenderDrawColor(window->renderer, 0x19, 0x019, 0x19, 0xFF);
    SDL_RenderPresent(window->renderer);
    usleep(time);
}

void datas_free(Datas *datas) {
    free(datas->rects);
}

void swap(Datas *datas, Window *window, int i, int j, int time) {
   int temp = datas->rects[i].h;
   datas->rects[i].h = datas->rects[j].h;
   datas->rects[j].h = temp;
   datas_render_when_sorting(datas, window, time, i, j);
}

// =======================================================> INSERTIONSORT 
void insertion_sort(Datas *datas, Window *window, int start, int end) {
    (void) start;
    for (int i = 0; i <= end; i++) {
        for (int j = 0; j <= end; j++) {
            if (datas->rects[i].h > datas->rects[j].h) {
                swap(datas, window, i, j, 100);
            }
        }
    }
}
// INSERTIONSORT <=======================================================

// =======================================================> SHAKERSORT
void shaker_sort(Datas *datas, Window *window, int start, int end) {
    (void) start;
    int p, i;
    for (p = 1; p <= end / 2; p++) {

        for (i = p - 1; i < end - p; i++)
            if (datas->rects[i].h < datas->rects[i+1].h)
                swap(datas, window, i, i + 1, 0);

        for (i = end - p - 1; i >= p; i--)
            if (datas->rects[i].h > datas->rects[i-1].h)
                swap(datas, window, i, i - 1, 0);
    }
}
// SHAKERSORT <=======================================================

// =======================================================> QUICKSORT
int partition (Datas *datas, Window *window, int start, int end) {
    int pivot = datas->rects[end].h;
    int i = (start - 1);
 
    for (int j = start; j <= end - 1; j++) {
        if (datas->rects[j].h > pivot) {
            i++;
            swap(datas, window, i, j, 0);
        }
    }
    swap(datas, window, i + 1, end, 0);
    return (i + 1);
}

void quick_sort(Datas *datas, Window *window, int start, int end) {
    if (start < end) {
        int pi = partition(datas, window, start, end);
        quick_sort(datas, window, start, pi - 1);
        quick_sort(datas, window, pi + 1, end);
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
        swap(datas, window, i, largest, 2000);
        heapify(datas, window, n, largest);
    }
}
 
void heap_sort(Datas *datas, Window *window, int start, int end) {
    (void) start;
    for (int i = end / 2; i >= 0; i--) {
        heapify(datas, window, end, i);
    }
 
    for (int i = end; i > 0; i--) {
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
            datas_render_when_sorting(datas, window, 1000, i, k);
            i++;
        } else {
            datas->rects[k].h = R[j];
            datas_render_when_sorting(datas, window, 1000, j, k);
            j++;
        }
        
        k++;
    }
    
    while (i < n1) {
        datas->rects[k].h = L[i];
        i++; k++;
        datas_render_when_sorting(datas, window, 1000, i, k);
    }
  
    while (j < n2) {
        datas->rects[k].h = R[j];
        j++; k++;
        datas_render_when_sorting(datas, window, 1000, j, k);
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
