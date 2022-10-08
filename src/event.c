#include <stdio.h>
#include <stdlib.h>
#include "easy2d_internals.h"
#include "easy2d.h"

#define SET_BIT(bit_field, index) bit_field |= 1 << (index)
#define UNSET_BIT(bit_field, index) bit_field &= ~(1 << (index))
#define TOGGLE_BIT(bit_field, index) bit_field ^= 1 << (index)
#define GET_BIT(bit_field, index) ((bit_field) & (1 << (index)))

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // identify which window called the window procedure
    char class_name[5];
    GetClassName(hwnd, class_name, 5);
    int window_id = atoi(class_name);
    e2d_Window* window = windows[window_id];
    
    switch (uMsg)
    {
        case WM_DESTROY:
        case WM_CLOSE: {
            window->keep_running = false;
        } break;

        case WM_SIZE: {
            window->client_width = LOWORD(lParam);
            window->client_height = HIWORD(lParam);
            window->resolution_scale_width = (float)window->resolution_width / window->client_width;
            window->resolution_scale_height = (float)window->resolution_height / window->client_height;    
        } break;

        case WM_MOUSEMOVE: {
            window->mouse_x = LOWORD(lParam);
            window->mouse_y = HIWORD(lParam);
        } break;

        case WM_LBUTTONDOWN: { SET_BIT(window->mouse_state, E2D_LMB); } break;
        case WM_LBUTTONUP: { UNSET_BIT(window->mouse_state, E2D_LMB); } break;
        
        case WM_RBUTTONDOWN: { SET_BIT(window->mouse_state, E2D_RMB); } break;
        case WM_RBUTTONUP: { UNSET_BIT(window->mouse_state, E2D_RMB); } break;
        
        case WM_MBUTTONDOWN: { SET_BIT(window->mouse_state, E2D_MMB); } break;
        case WM_MBUTTONUP: { UNSET_BIT(window->mouse_state, E2D_MMB); } break;

        case WM_MOUSEWHEEL: {
            union
            {
                uint16_t u;
                int16_t s;
            } delta = { HIWORD(wParam) };
        } break;
        
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

void e2d_handle_events()
{
    MSG message = { 0 };
    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

int e2d_get_mouse_x(e2d_Window* window)
{
    return window->mouse_x;
}

int e2d_get_mouse_y(e2d_Window* window)
{
    return window->mouse_y;
}

int e2d_get_mouse_x_in_framebuffer(e2d_Window* window)
{
    return window->mouse_x * window->resolution_scale_width;    
}

int e2d_get_mouse_y_in_framebuffer(e2d_Window* window)
{
    return window->mouse_y * window->resolution_scale_height;        
}

bool e2d_is_mouse_down(e2d_Window* window, e2d_MouseButton mouse_button)
{
    return GET_BIT(window->mouse_state, mouse_button);
}
