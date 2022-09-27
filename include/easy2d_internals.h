#ifndef EASY2D_INTERNALS_H
#define EASY2D_INTERNALS_H

#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

typedef struct e2d_Window
{
    int client_width;
    int client_height;

    int resolution_width;
    int resolution_height;

    int mouse_x;
    int mouse_y;
    
    float resolution_scale_width;
    float resolution_scale_height;

    uint32_t* framebuffer;

    bool keep_running;

    HWND window_handle;
    BITMAPINFO bitmap_info;
    HDC device_context;
} e2d_Window;

extern unsigned int window_count;
extern e2d_Window* windows[100];

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void internal_time_init();

#endif // EASY2D_INTERNALS_H
