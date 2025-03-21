#include <stdlib.h>
#include "easy2d.h"

int main()
{
    const int WIDTH = 640;
    const int HEIGHT = 480;

    // initialize internal E2D systems
    e2d_init();

    // create window
    e2d_Window* window = e2d_window_create(WIDTH, HEIGHT, "Hello, Easy2D!");
    e2d_set_target_framerate(60);

    // create framebuffer to draw to
    e2d_Texture framebuffer = {
        .width = WIDTH,
        .height = HEIGHT,
        .pixels = malloc(sizeof(e2d_Color) * WIDTH * HEIGHT)
    };

    // main loop
    while (!e2d_window_should_close(window))
    {
        e2d_handle_events();
        e2d_update_time();

        // clear the framebuffer
        e2d_texture_clear(&framebuffer, E2D_BLACK);

        // draw stuff to framebufer
        e2d_texture_draw_string(&framebuffer, "Hello from Easy2D!", 100, 100, E2D_WHITE);

        // display framebuffer to window
        e2d_texture_draw_to_window(&framebuffer, window);
    }

    e2d_window_destroy(window);
    e2d_close();

    free(framebuffer.pixels);
}
