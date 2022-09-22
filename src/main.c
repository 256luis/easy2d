#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include "easy2d.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define SCALE 0.125

#define WIDTH (WINDOW_WIDTH * SCALE)
#define HEIGHT (WINDOW_HEIGHT * SCALE)

int main()
{
    e2d_init();
    e2d_Window* window = e2d_create_window(WINDOW_WIDTH, WINDOW_HEIGHT, WIDTH, HEIGHT, "window!");
    e2d_show_window(window);

    int centerx = WIDTH/2;
    int centery = HEIGHT/2;

    float n = 0;
    int radius = 10;

    while (!e2d_should_window_close(window))
    {
        e2d_handle_events();

        int planetx = (cos(n) * radius) + centerx;
        int planety = (sin(n) * radius) + centery;
        
        e2d_clear_framebuffer(window, 0);
        
        e2d_set_pixel(window, centerx, centery, 0xffffffff);
        e2d_set_pixel(window, planetx, planety, 0xffffffff);

        e2d_draw_framebuffer(window);
        n += 0.1;
    }
    
    e2d_destroy_window(window);
}
