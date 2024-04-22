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

static
void draw_horizontal_line(e2d_Window* window, int x1, int x2, int y, e2d_Color color)
{
    // so we only go from left to right
    if (x1 > x2)
    {
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }

    for (int x = x1; x < x2; x++)
    {
        e2d_set_pixel(window, x, y, color);
    }
}

static
void draw_vertical_line(e2d_Window* window, int x, int y1, int y2, e2d_Color color)
{
    // so we only go from top to bottom
    if (y1 > y2)
    {
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }

    for (int y = y1; y < y2; y++)
    {
        e2d_set_pixel(window, x, y, color);
    }
}

// NOTE: this is a NAIVE line drawing algorithm
//       it may be slow because of floating point operations
// TODO: implement bresenham's line drawing algorithm
void e2d_draw_line(e2d_Window* window, int x1, int y1, int x2, int y2, e2d_Color color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dy == 0)
    {
        draw_horizontal_line(window, x1, x2, y1, color);
        return;
    }

    if (dx == 0)
    {
        draw_vertical_line(window, x1, y1, y2, color);
        return;
    }

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

void e2d_draw_rect_lines(e2d_Window* window, int x, int y, int width, int height, e2d_Color color)
{
    // top and bottom sides
    draw_horizontal_line(window, x, x + width, y, color);
    draw_horizontal_line(window, x, x + width, y + height - 1, color);

    // left and right sides
    draw_vertical_line(window, x, y, y + height, color);
    draw_vertical_line(window, x + width - 1, y, y + height, color);
}

void e2d_draw_rect_fill(e2d_Window* window, int x, int y, int width, int height, e2d_Color color)
{
    for (int row = y; row < y + height; row++)
    {
        for (int col = x; col < x + width; col++)
        {
            e2d_set_pixel(window, col, row, color);
        }
    }
}

void e2d_draw_triangle_lines(e2d_Window* window,
                             int x1, int y1,
                             int x2, int y2,
                             int x3, int y3,
                             e2d_Color color)
{
    e2d_draw_line(window, x1, y1, x2, y2, color);
    e2d_draw_line(window, x2, y2, x3, y3, color);
    e2d_draw_line(window, x3, y3, x1, y1, color);
}

void e2d_draw_image(e2d_Window* window, e2d_Image* image, int x, int y)
{
    for (int image_x = 0; image_x < image->width; image_x++)
    {
        for (int image_y = 0; image_y < image->height; image_y++)
        {
            int final_x = image_x + x;
            int final_y = image_y + y;

            if (final_x < 0 || final_x >= window->resolution_width) return;
            if (final_y < 0 || final_y >= window->resolution_height) return;

            uint32_t hex = image->pixels[image_x + (image_y * image->width)];
            window->framebuffer[final_x + (final_y * window->resolution_width)] = hex;
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
