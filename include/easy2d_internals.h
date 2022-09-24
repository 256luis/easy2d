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
    float resolution_scale_width;
    float resolution_scale_height;
    uint32_t* framebuffer;
    HWND window_handle;
    bool keep_running;
    BITMAPINFO bitmap_info;
    HDC device_context;
    int mouse_x;
    int mouse_y;
} e2d_Window;

#endif // EASY2D_INTERNALS_H
