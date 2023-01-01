#include "easy2d_internals.h"     

static inline
uint32_t e2d_color_to_hex(e2d_Color color)
{
    uint32_t hex =
        color.a << 24 |
        color.r << 16 |
        color.g <<  8 |
        color.b <<  0;

    return hex;
}

int e2d_get_framebuffer_length(e2d_Window* window)
{
    return window->resolution_width * window->resolution_height;
}

void e2d_set_pixel(e2d_Window* window, int x, int y, e2d_Color color)
{
    if (x < 0 || x >= window->resolution_width) return;
    if (y < 0 || y >= window->resolution_height) return;

    uint32_t hex = e2d_color_to_hex(color);
    window->framebuffer[x + (y * window->resolution_width)] = hex;
}

void e2d_clear_framebuffer(e2d_Window* window, e2d_Color color)
{
    uint32_t hex = e2d_color_to_hex(color);
    for (int i = 0; i < e2d_get_framebuffer_length(window); i++)
    {
        window->framebuffer[i] = hex;
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
