#include "easy2d_internals.h"

int e2d_get_framebuffer_length(e2d_Window* window)
{
    return window->resolution_width * window->resolution_height;
}

void e2d_set_pixel(e2d_Window* window, int x, int y, uint32_t color)
{
    if (x < 0 || x >= window->resolution_width) return;
    if (y < 0 || y >= window->resolution_height) return;

    window->framebuffer[x + (y * window->resolution_width)] = color;
}

void e2d_clear_framebuffer(e2d_Window* window, uint32_t color)
{
    for (int i = 0; i < e2d_get_framebuffer_length(window); i++)
    {
        window->framebuffer[i] = color;
    }
}

uint32_t* e2d_get_framebuffer_reference(e2d_Window* window)
{
    return window->framebuffer;
}

void e2d_draw_framebuffer(e2d_Window* window)
{
    StretchDIBits(
        window->device_context,     // hdc
        0, 0,                       // xDest, yDest
        window->client_width,       // DestWidth
        window->client_height,      // DestWidth
        0, 0,                       // xSrc, ySrc
        window->resolution_width,   // SrcWidth
        window->resolution_height,  // SrcHeight
        window->framebuffer,                // lpBits
        &window->bitmap_info,       // lpBmi
        DIB_RGB_COLORS,             // iUsage
        SRCCOPY
    );
}
