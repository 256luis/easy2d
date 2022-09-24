#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "easy2d.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define SCALE 0.5

int main()
{
    const int WIDTH = WINDOW_WIDTH * SCALE;
    const int HEIGHT = WINDOW_HEIGHT * SCALE;
    
    e2d_init();
    e2d_Window* window = e2d_create_window(WINDOW_WIDTH, WINDOW_HEIGHT, WIDTH, HEIGHT, "window!");
    e2d_show_window(window);
    
    while (!e2d_should_window_close(window))
    {
        e2d_handle_events();
        e2d_clear_framebuffer(window, 0);

        int x = e2d_get_mouse_x_in_framebuffer(window);
        int y = e2d_get_mouse_y_in_framebuffer(window);

        e2d_draw_framebuffer(window);
    }
    
    e2d_destroy_window(window);
    return 0;
}
