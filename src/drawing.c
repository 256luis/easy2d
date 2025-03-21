#include <stdio.h>
#include <math.h>
#include "easy2d.h"
#include "easy2d_internals.h"

void e2d_texture_set_pixel(e2d_Texture* texture, int x, int y, e2d_Color color)
{
    if (x < 0 || x >= texture->width) return;
    if (y < 0 || y >= texture->height) return;

    e2d_Color background_color = texture->pixels[x + (y * texture->width)];

    float foreground_alpha_percent = color.a / 255.f;
    float background_alpha_percent = background_color.a / 255.f;
    uint8_t blended_alpha = color.a + background_color.a * (1 - background_alpha_percent);

    e2d_Color new_color = {
        .r = (color.r * foreground_alpha_percent) + (background_color.r * (1 - foreground_alpha_percent)),
        .g = (color.g * foreground_alpha_percent) + (background_color.g * (1 - foreground_alpha_percent)),
        .b = (color.b * foreground_alpha_percent) + (background_color.b * (1 - foreground_alpha_percent)),
        .a = blended_alpha
    };

    // uint32_t hex = e2d_color_to_hex(new_color);
    texture->pixels[x + (y * texture->width)] = new_color;
}

static
void draw_horizontal_line(e2d_Texture* texture, int x1, int x2, int y, e2d_Color color)
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
        e2d_texture_set_pixel(texture, x, y, color);
    }
}

static
void draw_vertical_line(e2d_Texture* texture, int x, int y1, int y2, e2d_Color color)
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
        e2d_texture_set_pixel(texture, x, y, color);
    }
}

// NOTE: this is a NAIVE line drawing algorithm
//       it may be slow because of floating point operations
// TODO: implement bresenham's line drawing algorithm
void e2d_texture_draw_line(e2d_Texture* texture, int x1, int y1, int x2, int y2, e2d_Color color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dy == 0)
    {
        draw_horizontal_line(texture, x1, x2, y1, color);
        return;
    }

    if (dx == 0)
    {
        draw_vertical_line(texture, x1, y1, y2, color);
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
            e2d_texture_set_pixel(texture, x, y, color);

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
            e2d_texture_set_pixel(texture, x, y, color);

            x += slope;
            y++;
        }
    }
}

void e2d_texture_draw_rect_lines(e2d_Texture* texture, int x, int y, int width, int height, e2d_Color color)
{
    // top and bottom sides
    draw_horizontal_line(texture, x, x + width, y, color);
    draw_horizontal_line(texture, x, x + width, y + height - 1, color);

    // left and right sides
    draw_vertical_line(texture, x, y + 1, y + height - 1, color);
    draw_vertical_line(texture, x + width - 1, y + 1, y + height - 1, color);
}

void e2d_texture_draw_rect_fill(e2d_Texture* texture, int x, int y, int width, int height, e2d_Color color)
{
    for (int row = y; row < y + height; row++)
    {
        for (int col = x; col < x + width; col++)
        {
            e2d_texture_set_pixel(texture, col, row, color);
        }
    }
}

void e2d_texture_draw_triangle_lines(e2d_Texture* texture,
                             int x1, int y1,
                             int x2, int y2,
                             int x3, int y3,
                             e2d_Color color)
{
    e2d_texture_draw_line(texture, x1, y1, x2, y2, color);
    e2d_texture_draw_line(texture, x2, y2, x3, y3, color);
    e2d_texture_draw_line(texture, x3, y3, x1, y1, color);
}

void e2d_texture_clear(e2d_Texture* texture, e2d_Color color)
{
    for (int i = 0; i < texture->width * texture->height; i++)
    {
        texture->pixels[i] = color;
    }
}

void e2d_texture_draw_to_window(e2d_Texture* texture, e2d_Window* window)
{
    window->bitmap_info.bmiHeader.biWidth = texture->width;
    window->bitmap_info.bmiHeader.biHeight = -texture->height;

    StretchDIBits(
        window->device_context,     // hdc
        0, 0,                       // xDest, yDest
        window->width,       // DestWidth
        window->height,      // DestWidth
        0, 0,                       // xSrc, ySrc
        texture->width,   // SrcWidth
        texture->height,  // SrcHeight
        texture->pixels,                // lpBits
        &window->bitmap_info,       // lpBmi
        DIB_RGB_COLORS,             // iUsage
        SRCCOPY
    );
}
