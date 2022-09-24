#ifndef EASY2D_H
#define EASY2D_H

#include <stdint.h>
#include <stdbool.h>

typedef struct e2d_Window e2d_Window;

void e2d_init();
e2d_Window* e2d_create_window(int client_width, int client_height, int resolution_width, int resolution_height, const char* title);
void e2d_destroy_window(e2d_Window* window);
bool e2d_should_window_close(e2d_Window* window);

void e2d_handle_events();
int e2d_get_mouse_x(e2d_Window* window);
int e2d_get_mouse_y(e2d_Window* window);
int e2d_get_mouse_x_in_framebuffer(e2d_Window* window);
int e2d_get_mouse_y_in_framebuffer(e2d_Window* window);

void e2d_set_pixel(e2d_Window* window, int x, int y, uint32_t color);
int e2d_get_framebuffer_length(e2d_Window* window);
void e2d_clear_framebuffer(e2d_Window* window, uint32_t color);
void e2d_draw_framebuffer(e2d_Window* window);
uint32_t* e2d_get_framebuffer_reference(e2d_Window* window);

#endif // EASY2D_H
