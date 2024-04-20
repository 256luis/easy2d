#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "easy2d.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WIDTH (WINDOW_WIDTH)
#define HEIGHT (WINDOW_HEIGHT)
#define TARGET_FPS 60

#define STAR_COUNT 50000
#define DEPTH 80

typedef struct Star
{
    float x;
    float y;
    float z;
} Star;

int compare(const void* s1, const void* s2)
{
    return ((Star*)s1)->z > ((Star*)s2)->z ? -1 : 1;
}

int main()
{
    e2d_init();
    e2d_Window* window = e2d_create_window(WINDOW_WIDTH, WINDOW_HEIGHT, WIDTH, HEIGHT, "WINDOW");
    e2d_set_target_framerate(TARGET_FPS);

    // Star stars[STAR_COUNT];
    Star* stars = malloc(STAR_COUNT * sizeof(Star));
    for (int i = 0; i < STAR_COUNT; i++)
    {
        stars[i] = (Star){
            .x = rand() % WIDTH,
            .y = rand() % HEIGHT,
            .z = ((rand() % (DEPTH * 100)) / 100.0) + 1
        };
    }

    qsort(stars, STAR_COUNT, sizeof(Star), compare);
    
    int star_speed = 25;

    while (!e2d_should_window_close(window) && !e2d_is_key_pressed(window, E2D_KEY_ESC))
    {
        e2d_handle_events();
        e2d_update_time();

        // -------------------------------

        double fps = 1 / e2d_get_delta_time();

        for (int i = 0; i < STAR_COUNT; i++)
        {
            stars[i].y += (1 / stars[i].z) * star_speed * e2d_get_delta_time();
            stars[i].x += (1 / stars[i].z) * star_speed * e2d_get_delta_time();

            if (stars[i].x > WIDTH) stars[i].x -= WIDTH;
            if (stars[i].y > HEIGHT) stars[i].y -= HEIGHT;
        }

        // -------------------------------

        e2d_clear_framebuffer(window, E2D_BLACK);
        
        // -------------------------------

        for (int i = 0; i < STAR_COUNT; i++)
        {
            int luminance = 255 / stars[i].z;
            e2d_Color color = {
                .r = luminance,
                .g = luminance,
                .b = luminance,
                .a = 255
            };
            e2d_set_pixel(window, stars[i].x, stars[i].y, color);
            
        }        
        
        // -------------------------------

        // draw fps in upper left corner
        char fps_string[10] = {0};
        sprintf(fps_string, "FPS: %d", (int)fps);
        e2d_draw_string(window, fps_string, 0, 0, E2D_GREEN);
        
        e2d_draw_framebuffer(window);
    }
    
    e2d_destroy_window(window);
    e2d_close();
    
    return 0;
}
