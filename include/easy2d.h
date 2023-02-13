#ifndef EASY2D_H
#define EASY2D_H

#include <stdint.h>
#include <stdbool.h>

#define E2D_BLACK     ((e2d_Color){  0,   0,   0, 255})
#define E2D_WHITE     ((e2d_Color){255, 255, 255, 255})
#define E2D_RED       ((e2d_Color){255,   0,   0, 255})
#define E2D_ORANGE    ((e2d_Color){255, 128,   0, 255})
#define E2D_YELLOW    ((e2d_Color){255, 255,   0, 255})
#define E2D_LIME      ((e2d_Color){128, 255,   0, 255})
#define E2D_GREEN     ((e2d_Color){  0, 255,   0, 255})
#define E2D_TEAL      ((e2d_Color){  0, 255, 128, 255})
#define E2D_CYAN      ((e2d_Color){  0, 255, 255, 255})
#define E2D_LIGHTBLUE ((e2d_Color){  0, 128, 255, 255})
#define E2D_BLUE      ((e2d_Color){  0,   0, 255, 255})
#define E2D_PURPLE    ((e2d_Color){127,   0, 255, 255})
#define E2D_MAGENTA   ((e2d_Color){255,   0, 255, 255})
#define E2D_PINK      ((e2d_Color){255,   0, 127, 255})

typedef struct e2d_Window e2d_Window;

typedef struct e2d_Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} e2d_Color;

typedef enum e2d_MouseButton
{
    E2D_LMB, E2D_RMB, E2D_MMB,
    E2D_MOUSEBUTTON_COUNT
} e2d_MouseButton;

typedef enum e2d_Key
{
    // ALPHABET
    E2D_KEY_A, E2D_KEY_B, E2D_KEY_C, E2D_KEY_D, E2D_KEY_E, E2D_KEY_F, 
    E2D_KEY_G, E2D_KEY_H, E2D_KEY_I, E2D_KEY_J, E2D_KEY_K, E2D_KEY_L, 
    E2D_KEY_M, E2D_KEY_N, E2D_KEY_O, E2D_KEY_P, E2D_KEY_Q, E2D_KEY_R, 
    E2D_KEY_S, E2D_KEY_T, E2D_KEY_U, E2D_KEY_V, E2D_KEY_W, E2D_KEY_X, 
    E2D_KEY_Y, E2D_KEY_Z,

    // NUMBERS
    E2D_KEY_0, E2D_KEY_1, E2D_KEY_2, E2D_KEY_3, E2D_KEY_4,
    E2D_KEY_5, E2D_KEY_6, E2D_KEY_7, E2D_KEY_8, E2D_KEY_9,

    // NUMPAD
    E2D_KEY_NUM0, E2D_KEY_NUM1, E2D_KEY_NUM2, E2D_KEY_NUM3, E2D_KEY_NUM4,
    E2D_KEY_NUM5, E2D_KEY_NUM6, E2D_KEY_NUM7, E2D_KEY_NUM8, E2D_KEY_NUM9,
    
    E2D_KEY_NUMDIVIDE, E2D_KEY_NUMMULTIPLY, E2D_KEY_NUMMINUS,
    E2D_KEY_NUMPLUS,   E2D_KEY_NUMPERIOD,   E2D_KEY_NUMENTER,
    E2D_KEY_NUMEQUALS, 
    
    // SPECIAL CHARACTERS    
    E2D_KEY_BACKTICK,     E2D_KEY_MINUS,        E2D_KEY_EQUALS,
    E2D_KEY_TAB,          E2D_KEY_OPENBRACKET, E2D_KEY_CLOSEBRACKET,
    E2D_KEY_BACKSLASH,    E2D_KEY_SEMICOLON,   E2D_KEY_APOSTROPHE,
    E2D_KEY_RETURN,       E2D_KEY_COMMA,       E2D_KEY_PERIOD, 
    E2D_KEY_FORWARDSLASH, E2D_KEY_SPACE,           E2D_KEY_BACKSPACE,

    // ARROW KEYS
    E2D_KEY_ARROWUP,   E2D_KEY_ARROWDOWN,
    E2D_KEY_ARROWLEFT, E2D_KEY_ARROWRIGHT,
    
    // F-KEYS
    E2D_KEY_F1, E2D_KEY_F2,  E2D_KEY_F3,  E2D_KEY_F4,
    E2D_KEY_F5, E2D_KEY_F6,  E2D_KEY_F7,  E2D_KEY_F8,
    E2D_KEY_F9, E2D_KEY_F10, E2D_KEY_F11, E2D_KEY_F12,

    // MODIFIERS
    E2D_KEY_SHIFT, E2D_KEY_CTRL, E2D_KEY_LALT, E2D_KEY_RALT,

    // MISCELLANEOUS
    E2D_KEY_ESC,      E2D_KEY_PAUSE,  E2D_KEY_SCRLLK, E2D_KEY_INSERT,
    E2D_KEY_DELETE,   E2D_KEY_HOME,   E2D_KEY_PAGEUP, E2D_KEY_PAGEDOWN,
    E2D_KEY_END,      E2D_KEY_NUMLK,  E2D_KEY_LWIN,   E2D_KEY_RWIN,     
    E2D_KEY_CAPSLOCK,

    E2D_KEY_COUNT
} e2d_Key;

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
bool e2d_is_key_down(e2d_Window* window, e2d_Key key);
bool e2d_is_key_pressed(e2d_Window* window, e2d_Key key);
bool e2d_is_key_released(e2d_Window* window, e2d_Key key);

void e2d_set_pixel(e2d_Window* window, int x, int y, e2d_Color color);
void e2d_draw_line(e2d_Window* window, int x1, int y1, int x2, int y2, e2d_Color color);
void e2d_draw_rect_lines(e2d_Window* window, int x, int y, int width, int height, e2d_Color color);
void e2d_draw_rect_fill(e2d_Window* window, int x, int y, int width, int height, e2d_Color color);
void e2d_draw_triangle_lines(e2d_Window* window, int x1, int y1, int x2, int y2, int x3, int y3, e2d_Color color);
int e2d_get_framebuffer_length(e2d_Window* window);
uint32_t* e2d_get_framebuffer_reference(e2d_Window* window);
void e2d_clear_framebuffer(e2d_Window* window, e2d_Color color);
void e2d_draw_framebuffer(e2d_Window* window);

void e2d_update_time();
double e2d_get_time();
double e2d_get_delta_time();
void e2d_set_target_framerate(int target_framerate);
void e2d_limit_framerate();

#endif // EASY2D_H
