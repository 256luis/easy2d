#include <stdio.h>
#include <math.h>
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

void e2d_set_pixel(e2d_Window* window, int x, int y, e2d_Color color)
{
    if (x < 0 || x >= window->resolution_width) return;
    if (y < 0 || y >= window->resolution_height) return;

    uint32_t hex = e2d_color_to_hex(color);
    window->framebuffer[x + (y * window->resolution_width)] = hex;
}

// NOTE: this is a NAIVE line drawing algorithm
//       it may be slow because of floating point operations
// TODO: implement bresenham's line drawing algorithm
void e2d_draw_line(e2d_Window* window, int x1, int y1, int x2, int y2, e2d_Color color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    // if more horizontal than vertical
    if (abs(dx) > abs(dy))
    {
        float slope = (float)dy / dx;
        
        // so we only go from left to right
        if (x1 > x2)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;

            temp = y1;
            y1 = y2;
            y2 = temp;
        }

        // iterate over all columns
        int x = x1;
        float y = y1;
        while (x < x2)
        {
            e2d_set_pixel(window, x, y, color);
            
            x++;
            y += slope;
        }
    }
    else
    {
        float slope = (float)dx / dy;
        
        // so we only go from top to bottom
        if (y1 > y2)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;

            temp = y1;
            y1 = y2;
            y2 = temp;
        }

        // iterate over all rows
        float x = x1;
        int y = y1;
        while (y < y2)
        {
            e2d_set_pixel(window, x, y, color);
            
            x += slope;
            y++;
        }
    }
}

int e2d_get_framebuffer_length(e2d_Window* window)
{
    return window->resolution_width * window->resolution_height;
}

uint32_t* e2d_get_framebuffer_reference(e2d_Window* window)
{
    return window->framebuffer;
}

void e2d_clear_framebuffer(e2d_Window* window, e2d_Color color)
{
    uint32_t hex = e2d_color_to_hex(color);
    for (int i = 0; i < e2d_get_framebuffer_length(window); i++)
    {
        window->framebuffer[i] = hex;
    }
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
