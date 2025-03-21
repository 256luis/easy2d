///
/// @brief Easy2D - Quick and Easy 2D Graphics
///
/// Easy2D is a lightweight and easy-to-use 2D graphics library for creating simple
/// graphical applications.
/// It provides a straightforward API for window management, input handling, texture
/// manipulation, and basic drawing.
///
/// Basic usage:
/// @code
/// #include "easy2d.h"
///
/// int main()
/// {
///     const int WIDTH = 640;
///     const int HEIGHT = 480;
///
///     // initialize internal E2D systems
///     e2d_init();
///
///     // create window
///     e2d_Window* window = e2d_create_window(WIDTH, HEIGHT, "Hello, Easy2D Window!");
///     e2d_set_target_framerate(60);
///
///     // framebuffer to draw to
///     e2d_Texture framebuffer = {
///         .width = WIDTH,
///         .height = HEIGHT,
///         .pixels = malloc(sizeof(e2d_Color) * WIDTH * HEIGHT)
///     }
///
///     // main render loop
///     while (!e2d_should_window_close(window))
///     {
///         e2d_handle_events();
///         e2d_update_time();
///
///         // clear the framebuffer
///         e2d_texture_clear(&texture, E2D_BLACK);
///
///         // draw stuff to framebuffer
///         e2d_texture_draw_string(&texture, "Hello from Easy2D!", 100, 100, E2D_WHITE);
///
///         // display framebuffer on window
///         e2d_texture_draw_to_window(&texture, window);
///     }
///
///    e2d_destroy_window(window);
///    e2d_close();
/// }
/// @endcode
///

#ifndef EASY2D_H
#define EASY2D_H

#include <stdint.h>
#include <stdbool.h>

#define E2D_BLACK     ((e2d_Color){ .r =   0, .g =    0, .b =   0, .a = 255})
#define E2D_WHITE     ((e2d_Color){ .r = 255, .g =  255, .b = 255, .a = 255})
#define E2D_RED       ((e2d_Color){ .r = 255, .g =    0, .b =   0, .a = 255})
#define E2D_ORANGE    ((e2d_Color){ .r = 255, .g =  128, .b =   0, .a = 255})
#define E2D_YELLOW    ((e2d_Color){ .r = 255, .g =  255, .b =   0, .a = 255})
#define E2D_LIME      ((e2d_Color){ .r = 128, .g =  255, .b =   0, .a = 255})
#define E2D_GREEN     ((e2d_Color){ .r =   0, .g =  255, .b =   0, .a = 255})
#define E2D_TEAL      ((e2d_Color){ .r =   0, .g =  255, .b = 128, .a = 255})
#define E2D_CYAN      ((e2d_Color){ .r =   0, .g =  255, .b = 255, .a = 255})
#define E2D_LIGHTBLUE ((e2d_Color){ .r =   0, .g =  128, .b = 255, .a = 255})
#define E2D_BLUE      ((e2d_Color){ .r =   0, .g =    0, .b = 255, .a = 255})
#define E2D_PURPLE    ((e2d_Color){ .r = 127, .g =    0, .b = 255, .a = 255})
#define E2D_MAGENTA   ((e2d_Color){ .r = 255, .g =    0, .b = 255, .a = 255})
#define E2D_PINK      ((e2d_Color){ .r = 255, .g =    0, .b = 127, .a = 255})

///
/// @brief Opaque window struct.
///
typedef struct e2d_Window e2d_Window;

///
/// @brief Contains the RGBA components of a color
///
typedef union e2d_Color
{
    struct
    {
        uint8_t b; ///< Blue component of the pixel
        uint8_t g; ///< Green component of the pixel
        uint8_t r; ///< Red component of the pixel
        uint8_t a; ///< Alpha component of the pixel
    };

    uint32_t hex;  ///< The RGBA components aggregated into a single `uint32_t`
} e2d_Color;

///
/// @brief Contains information about a texture
///
typedef struct e2d_Texture
{
    int width;         ///< Width of the texture in pixels
    int height;        ///< Height of the texture in pixels
    e2d_Color* pixels; ///< Array of {@link e2d_Color}s
} e2d_Texture;

///
/// @brief The different recognized mouse buttons
///
typedef enum e2d_MouseButton
{
    E2D_LMB, E2D_RMB, E2D_MMB,
    E2D_MOUSEBUTTON_COUNT ///< Used internally.
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

    E2D_KEY_COUNT ///< Used internally.
} e2d_Key;

///
/// @brief Initializes internal E2D systems
///
/// This function must be called before any other E2D function. Failure to do so may
/// invoke undefined behavior.
///
void e2d_init();

///
/// @brief Deinitializes and frees internal E2D systems
///
/// Call this function once done with E2D.
///
void e2d_close();
e2d_Window* e2d_create_window(int client_width, int client_height, int resolution_width, int resolution_height, const char* title);
void e2d_set_window_title(e2d_Window* window, const char* title);
void e2d_destroy_window(e2d_Window* window);
bool e2d_should_window_close(e2d_Window* window);

void e2d_handle_events();
int e2d_get_mouse_x(e2d_Window* window);
int e2d_get_mouse_y(e2d_Window* window);
int e2d_get_mouse_wheel_delta(e2d_Window* window);
bool e2d_is_mouse_down(e2d_Window* window, e2d_MouseButton mouse_button);
bool e2d_is_mouse_pressed(e2d_Window* window, e2d_MouseButton mouse_button);
bool e2d_is_mouse_released(e2d_Window* window, e2d_MouseButton mouse_button);
bool e2d_is_key_down(e2d_Window* window, e2d_Key key);
bool e2d_is_key_pressed(e2d_Window* window, e2d_Key key);
bool e2d_is_key_released(e2d_Window* window, e2d_Key key);

void e2d_texture_set_pixel(e2d_Texture* texture, int x, int y, e2d_Color color);
void e2d_texture_draw_line(e2d_Texture* texture, int x1, int y1, int x2, int y2, e2d_Color color);
void e2d_texture_draw_rect_lines(e2d_Texture* texture, int x, int y, int width, int height, e2d_Color color);
void e2d_texture_draw_rect_fill(e2d_Texture* texture, int x, int y, int width, int height, e2d_Color color);
void e2d_texture_draw_triangle_lines(e2d_Texture* texture, int x1, int y1, int x2, int y2, int x3, int y3, e2d_Color color);
void e2d_texture_clear(e2d_Texture* texture, e2d_Color color);
void e2d_texture_draw_to_window(e2d_Texture* texture, e2d_Window* window);

void e2d_texture_draw_char(e2d_Texture* texture, char c, int x, int y, e2d_Color color);
void e2d_texture_draw_string(e2d_Texture* texture, const char* s, int x, int y, e2d_Color color);

e2d_Texture* e2d_texture_load(const char* path);
void e2d_texture_destroy(e2d_Texture* texture);
void e2d_texture_copy_to_texture(e2d_Texture* source_texture, int source_x, int source_y, int source_width, int source_height, e2d_Texture* destination_texture, int destination_x, int destination_y, int destination_width, int destination_height);

void e2d_update_time();
double e2d_get_time();
double e2d_get_delta_time();
void e2d_set_target_framerate(int target_framerate);
void e2d_limit_framerate();

#endif // EASY2D_H
