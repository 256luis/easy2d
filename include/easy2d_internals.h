#ifndef EASY2D_INTERNALS_H
#define EASY2D_INTERNALS_H

#include <stdint.h>
#include <stdbool.h>
#include <windows.h>
#include "easy2d.h"

typedef struct e2d_Window
{
    int width;
    int height;

    /* int resolution_width; */
    /* int resolution_height; */

    /* float resolution_scale_width; */
    /* float resolution_scale_height; */

    int mouse_x;
    int mouse_y;
    int mouse_wheel_delta;
    bool mouse_down_state[E2D_MOUSEBUTTON_COUNT];
    bool mouse_pressed_state[E2D_MOUSEBUTTON_COUNT];
    bool mouse_released_state[E2D_MOUSEBUTTON_COUNT];

    bool key_down_state[E2D_KEY_COUNT];
    bool key_pressed_state[E2D_KEY_COUNT];
    bool key_released_state[E2D_KEY_COUNT];

    // uint32_t* framebuffer;

    bool keep_running;

    HWND window_handle;
    BITMAPINFO bitmap_info;
    HDC device_context;
} e2d_Window;

extern unsigned int window_count;
extern e2d_Window* windows[100];

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void internal_time_init();
void vk_to_e2d_lut_init();

#endif // EASY2D_INTERNALS_H
