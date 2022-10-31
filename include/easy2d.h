#ifndef EASY2D_H
#define EASY2D_H

#include <stdint.h>
#include <stdbool.h>

#define E2D_COLOR(R, G, B, A) ((uint32_t)((((uint8_t)(A)) << 24) | (((uint8_t)(R)) << 16) | (((uint8_t)(G)) << 8) | (((uint8_t)(B)) << 0)))

typedef struct e2d_Window e2d_Window;

typedef enum e2d_MouseButton
{
    E2D_LMB, E2D_RMB, E2D_MMB,
    E2D_MOUSEBUTTON_COUNT
} e2d_MouseButton;

void e2d_init();
void e2d_close();
e2d_Window* e2d_create_window(int client_width, int client_height, int resolution_width, int resolution_height, const char* title);
void e2d_set_window_title(e2d_Window* window, const char* title);
void e2d_destroy_window(e2d_Window* window);
bool e2d_should_window_close(e2d_Window* window);

void e2d_handle_events();
int e2d_get_mouse_x(e2d_Window* window);
int e2d_get_mouse_y(e2d_Window* window);
int e2d_get_mouse_x_in_framebuffer(e2d_Window* window);
int e2d_get_mouse_y_in_framebuffer(e2d_Window* window);
int e2d_get_mouse_wheel_delta(e2d_Window* window);
bool e2d_is_mouse_down(e2d_Window* window, e2d_MouseButton mouse_button);
bool e2d_is_mouse_pressed(e2d_Window* window, e2d_MouseButton mouse_button);
bool e2d_is_mouse_released(e2d_Window* window, e2d_MouseButton mouse_button);

void e2d_set_pixel(e2d_Window* window, int x, int y, uint32_t color);
int e2d_get_framebuffer_length(e2d_Window* window);
void e2d_clear_framebuffer(e2d_Window* window, uint32_t color);
void e2d_draw_framebuffer(e2d_Window* window);
uint32_t* e2d_get_framebuffer_reference(e2d_Window* window);

void e2d_update_time();
double e2d_get_time();
double e2d_get_delta_time();
void e2d_set_target_framerate(int target_framerate);
void e2d_limit_framerate();

#endif // EASY2D_H
