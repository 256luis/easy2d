#include "easy2d_internals.h"

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
