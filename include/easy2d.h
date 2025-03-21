///
/// @file easy2d.h
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
///     // main loop
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
/// Opaque window struct
///
typedef struct e2d_Window e2d_Window;

///
/// Contains the RGBA components of a color
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
/// Contains information about a texture
///
typedef struct e2d_Texture
{
    int width;         ///< Width of the texture in pixels
    int height;        ///< Height of the texture in pixels
    e2d_Color* pixels; ///< Array of {@link e2d_Color}s
} e2d_Texture;

///
/// The different recognized mouse buttons
///
/// @see   e2d_is_mouse_down
/// @see   e2d_is_mouse_pressed
/// @see   e2d_is_mouse_released
///
typedef enum e2d_MouseButton
{
    E2D_LMB, E2D_RMB, E2D_MMB,
    E2D_MOUSEBUTTON_COUNT ///< Used internally.
} e2d_MouseButton;

///
/// The different recognized keyboard keys
///
/// @see   e2d_is_key_down
/// @see   e2d_is_key_pressed
/// @see   e2d_is_key_released
///
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
/// Initializes internal E2D systems
///
/// @note This function must be called before any other E2D function. Failure to do so may
///       invoke undefined behavior.
///
void e2d_init();

///
/// Deinitializes and frees internal E2D systems
///
/// Call this function once done with E2D.
///
void e2d_close();

///
/// Creates an e2d_Window
///
/// @param   width  The width of the window in pixels
/// @param   height The height of the window in pixels
/// @param   title  The null-terminated string to be displayed at the title bar
/// @returns        A pointer to the created {@link e2d_Window}
///
e2d_Window* e2d_create_window(int width, int height, const char* title);

///
/// Sets the window title to be displayed at the title bar
///
/// @param window A pointer to the {@link e2d_Window} whose title is to be modified.
/// @param title  The null-terminated string to be displayed at the title bar.
///
void e2d_set_window_title(e2d_Window* window, const char* title);

///
/// Destroys the e2d_Window
///
/// @param window A pointer to the {@link e2d_Window} to destroy.
///
void e2d_destroy_window(e2d_Window* window);

///
/// Checks if a particular {@link e2d_Window} should be closed
///
/// @param window A pointer to the {@link e2d_Window} to check
/// @returns      true if the window should close, otherwise false
///
bool e2d_should_window_close(e2d_Window* window);

///
/// Handles mouse, keyboard, and windows events
///
/// Call this function at the start of the main loop.
///
void e2d_handle_events();

///
/// Gets the position of the mouse along the x-axis relative to the window
///
/// @param window The {@link e2d_Window} to find the position of the mouse relative to
/// @returns      The position of the mouse along the x-axis relative to the window
///
int e2d_get_mouse_x(e2d_Window* window);

///
/// Gets the position of the mouse along the y-axis relative to the window
///
/// @param window The {@link e2d_Window} to find the position of the mouse relative to
/// @returns      The position of the mouse along the y-axis relative to the window
///
int e2d_get_mouse_y(e2d_Window* window);

///
/// Gets the mouse wheel delta
///
/// @param window The focused {@link e2d_Window}
/// @returns      The mouse wheel delta
///
int e2d_get_mouse_wheel_delta(e2d_Window* window);

///
/// Checks if the passed {@link e2d_MouseButton} is currently held down
///
/// @param window       The focused {@link e2d_Window}
/// @param mouse_button The {@link e2d_MouseButton} to check for
/// @returns            true or false
///
bool e2d_is_mouse_down(e2d_Window* window, e2d_MouseButton mouse_button);

///
/// Checks if the passed {@link e2d_MouseButton} has just been pressed
///
/// @param window       The focused {@link e2d_Window}
/// @param mouse_button The {@link e2d_MouseButton} to check for
/// @returns            true or false
///
bool e2d_is_mouse_pressed(e2d_Window* window, e2d_MouseButton mouse_button);

///
/// Checks if the passed {@link e2d_MouseButton} has just been released
///
/// @param window       The focused {@link e2d_Window}
/// @param mouse_button The {@link e2d_MouseButton} to check for
/// @returns            true or false
///
bool e2d_is_mouse_released(e2d_Window* window, e2d_MouseButton mouse_button);

///
/// Checks if the passed {@link e2d_Key} is currently held down
///
/// @param window       The focused {@link e2d_Window}
/// @param key          The {@link e2d_Key} to check for
/// @returns            true or false
///
bool e2d_is_key_down(e2d_Window* window, e2d_Key key);

///
/// Checks if the passed {@link e2d_Key} has just been pressed
///
/// @param window       The focused {@link e2d_Window}
/// @param key          The {@link e2d_Key} to check for
/// @returns            true or false
///
bool e2d_is_key_pressed(e2d_Window* window, e2d_Key key);

///
/// Checks if the passed {@link e2d_Key} is just been released
///
/// @param window       The focused {@link e2d_Window}
/// @param key          The {@link e2d_Key} to check for
/// @returns            true or false
///
bool e2d_is_key_released(e2d_Window* window, e2d_Key key);

///
/// Draws a pixel onto a texture
///
/// @param texture A pointer to the {@link e2d_Texture} to draw to
/// @param x       The x-coordinate of the pixel
/// @param y       The y-coordinate of the pixel
/// @param color   The {@link e2d_Color} of the pixel to draw
///
/// @note          If the specified x and y coordinates are outside the bounds of the
///                texture, it will be ignored.
///
void e2d_texture_set_pixel(e2d_Texture* texture, int x, int y, e2d_Color color);

///
/// Draws a line onto a texture
///
/// @param texture A pointer to the {@link e2d_Texture} to draw to
/// @param x1      The starting x-coordinate of the line
/// @param y1      The starting y-coordinate of the line
/// @param x2      The ending x-coordinate of the line
/// @param y2      The ending y-coordinate of the line
/// @param color   The {@link e2d_Color} of the line to draw
///
void e2d_texture_draw_line(e2d_Texture* texture, int x1, int y1, int x2, int y2, e2d_Color color);

///
/// Draws the outline of a rectangle onto a texture
///
/// @param texture A pointer to the {@link e2d_Texture} to draw to
/// @param x       The x-coordinate of the top-left corner of the rectangle
/// @param y       The y-coordinate of the top-left corner of the rectangle
/// @param width   The width of the rectangle in pixels
/// @param height   The height of the rectangle in pixels
/// @param color   The {@link e2d_Color} of the rectangle to draw
///
void e2d_texture_draw_rect_lines(e2d_Texture* texture, int x, int y, int width, int height, e2d_Color color);

///
/// Draws a filled rectangle onto a texture
///
/// @param texture A pointer to the {@link e2d_Texture} to draw to
/// @param x       The x-coordinate of the top-left corner of the rectangle
/// @param y       The y-coordinate of the top-left corner of the rectangle
/// @param width   The width of the rectangle in pixels
/// @param height   The height of the rectangle in pixels
/// @param color   The {@link e2d_Color} of the rectangle to draw
///
void e2d_texture_draw_rect_fill(e2d_Texture* texture, int x, int y, int width, int height, e2d_Color color);

///
/// Draws the outline of a triangle onto a texture
///
/// @param texture A pointer to the {@link e2d_Texture} to draw to
/// @param x1      The x-coordinate of the first vertex of the triangle
/// @param y1      The y-coordinate of the first vertex of the triangle
/// @param x2      The x-coordinate of the second vertex of the triangle
/// @param y2      The y-coordinate of the second vertex of the triangle
/// @param x3      The x-coordinate of the third vertex of the triangle
/// @param y3      The y-coordinate of the third vertex of the triangle
/// @param color   The {@link e2d_Color} of the rectangle to draw
///
void e2d_texture_draw_triangle_lines(e2d_Texture* texture, int x1, int y1, int x2, int y2, int x3, int y3, e2d_Color color);

///
/// Clears the texture and fills it with the specified {@link e2d_Color}
///
/// @param texture A pointer to the {@link e2d_Texture} to clear
/// @param color   The {@link e2d_Color} to fill the texture with
///
void e2d_texture_clear(e2d_Texture* texture, e2d_Color color);

///
/// Draws a texture to a window
///
/// @param texture A pointer to the {@link e2d_Texture} to draw
/// @param window  A pointer to the {@link e2d_Window} to draw onto
///
/// @note The texture will automatically be stretched to fit the dimensions of the window.
///
void e2d_texture_draw_to_window(e2d_Texture* texture, e2d_Window* window);

///
/// Draws a character onto a texture
///
/// @param texture A pointer to the {@link e2d_Texture} to draw to
/// @param x       The position of the character along the x axis
/// @param y       The position of the character along the y axis
/// @param c       The character to draw
/// @param color   The {@link e2d_Color} of the character to draw
///
void e2d_texture_draw_char(e2d_Texture* texture, char c, int x, int y, e2d_Color color);

///
/// Draws a null-terminated string onto a texture
///
/// @param texture A pointer to the {@link e2d_Texture} to draw to
/// @param x       The position of the string along the x axis
/// @param y       The position of the string along the y axis
/// @param s       The string to draw
/// @param color   The {@link e2d_Color} of the string to draw
///
void e2d_texture_draw_string(e2d_Texture* texture, const char* s, int x, int y, e2d_Color color);

///
/// Loads an image from disk
///
/// @param path The relative path of the image
/// @returns    A pointer to a {@link e2d_Texture} containing the image
/// @see        e2d_texture_destroy
///
e2d_Texture* e2d_texture_load(const char* path);

///
/// Destroys a texture created with {@link e2d_texture_load}
///
/// @param texture A pointer to the {@link e2d_Texture} created with {@link
///                e2d_texture_load}
///
void e2d_texture_destroy(e2d_Texture* texture);

///
/// Copies a portion of a source texture onto a destination texture.
///
/// @param source_texture      A pointer to the {@link e2d_Texture} to copy from.
/// @param source_x            The x-coordinate of the top-left corner of the source region to copy.
/// @param source_y            The y-coordinate of the top-left corner of the source region to copy.
/// @param source_width        The width of the source region to copy.
/// @param source_height       The height of the source region to copy.
/// @param destination_texture A pointer to the {@link e2d_Texture} to copy to.
/// @param destination_x       The x-coordinate of the top-left corner where the source region will be placed on the destination texture.
/// @param destination_y       The y-coordinate of the top-left corner where the source region will be placed on the destination texture.
/// @param destination_width   The width of the destination region. If this differs from `source_width`, the source region will be scaled to fit.
/// @param destination_height  The height of the destination region. If this differs from `source_height`, the source region will be scaled to fit.
///
/// @note If the source coordinates and dimensions exceed the bounds of the source texture,
///       the texture is tiled.
/// @note Scaling of source texture has not yet been implemented.
///
void e2d_texture_copy_to_texture(e2d_Texture* source_texture, int source_x, int source_y, int source_width, int source_height, e2d_Texture* destination_texture, int destination_x, int destination_y, int destination_width, int destination_height);

///
/// Updates timing-related internal variables
///
/// @note Call this at the top of your main loop before calling any other timing-related
///       functions.
///
void e2d_update_time();

///
/// Gets a high resolution time stamp
///
/// @returns The current performance counter value
///
double e2d_get_time();

///
/// Gets the amount of time since {@link e2d_update_time} was called
///
/// @returns The amount of time since {@link e2d_update_time} was called in seconds
///
double e2d_get_delta_time();

///
/// Sets the target framerate for the application.
///
/// @param target_framerate The desired framerate (in frames per second).
///
/// @note This function does not enforce the framerate by itself. Framerate limiting is
///       enforced in {@link e2d_update_time}.
///
void e2d_set_target_framerate(int target_framerate);

#endif // EASY2D_H
