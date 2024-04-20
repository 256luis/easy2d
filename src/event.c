#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "easy2d_internals.h"
#include "easy2d.h"

#define VK_KEY_COUNT VK_OEM_CLEAR
int vk_to_e2d_lut[VK_KEY_COUNT];

inline
void vk_map_sequence_e2d(int vk_start, int e2d_start, int count)
{
    for (int i = 0, c = vk_start; i < count; i++)
    {
        vk_to_e2d_lut[i + c] = i + e2d_start;        
    }
}

// prepare LUT
void vk_to_e2d_lut_init()
{
    for (int i = 0; i < VK_KEY_COUNT; i++)
    {
        vk_to_e2d_lut[i] = -1;
    }
    
    vk_to_e2d_lut[VK_BACK]      = E2D_KEY_BACKSPACE;
    vk_to_e2d_lut[VK_TAB]       = E2D_KEY_TAB;
    vk_to_e2d_lut[VK_RETURN]    = E2D_KEY_RETURN;
    vk_to_e2d_lut[VK_CAPITAL]   = E2D_KEY_CAPSLOCK;
    vk_to_e2d_lut[VK_ESCAPE]    = E2D_KEY_ESC;
    vk_to_e2d_lut[VK_SPACE]     = E2D_KEY_SPACE;

    vk_to_e2d_lut[VK_PRIOR]     = E2D_KEY_PAGEUP;
    vk_to_e2d_lut[VK_NEXT]      = E2D_KEY_PAGEDOWN;
    vk_to_e2d_lut[VK_END]       = E2D_KEY_END;
    vk_to_e2d_lut[VK_HOME]      = E2D_KEY_HOME;

    vk_to_e2d_lut[VK_LEFT]      = E2D_KEY_ARROWLEFT;
    vk_to_e2d_lut[VK_UP]        = E2D_KEY_ARROWUP;
    vk_to_e2d_lut[VK_RIGHT]     = E2D_KEY_ARROWRIGHT;
    vk_to_e2d_lut[VK_DOWN]      = E2D_KEY_ARROWDOWN;

    vk_to_e2d_lut[VK_INSERT]    = E2D_KEY_INSERT;
    vk_to_e2d_lut[VK_DELETE]    = E2D_KEY_DELETE;

    vk_to_e2d_lut[VK_LWIN]      = E2D_KEY_LWIN;
    vk_to_e2d_lut[VK_RWIN]      = E2D_KEY_RWIN;

    vk_to_e2d_lut[VK_MULTIPLY]  = E2D_KEY_NUMMULTIPLY;
    vk_to_e2d_lut[VK_ADD]       = E2D_KEY_NUMPLUS;
    vk_to_e2d_lut[VK_SUBTRACT]  = E2D_KEY_NUMMINUS;
    vk_to_e2d_lut[VK_DECIMAL]   = E2D_KEY_NUMPERIOD;
    vk_to_e2d_lut[VK_DIVIDE]    = E2D_KEY_NUMDIVIDE;

    vk_to_e2d_lut[VK_NUMLOCK]   = E2D_KEY_NUMLK;
    vk_to_e2d_lut[VK_SCROLL]    = E2D_KEY_SCRLLK;

    vk_to_e2d_lut[VK_SHIFT]     = E2D_KEY_SHIFT; 
    vk_to_e2d_lut[VK_CONTROL]   = E2D_KEY_CTRL;  
    vk_to_e2d_lut[VK_LMENU]     = E2D_KEY_LALT;  
    vk_to_e2d_lut[VK_RMENU]     = E2D_KEY_RALT;

    vk_to_e2d_lut[VK_OEM_PLUS]  = E2D_KEY_EQUALS;
    vk_to_e2d_lut[VK_OEM_MINUS] = E2D_KEY_MINUS;
    vk_to_e2d_lut[VK_OEM_COMMA]  = E2D_KEY_COMMA;
    vk_to_e2d_lut[VK_OEM_PERIOD] = E2D_KEY_PERIOD;
    
    vk_to_e2d_lut[VK_OEM_3]     = E2D_KEY_BACKTICK;
    vk_to_e2d_lut[VK_OEM_4]     = E2D_KEY_OPENBRACKET;
    vk_to_e2d_lut[VK_OEM_6]     = E2D_KEY_CLOSEBRACKET;
    vk_to_e2d_lut[VK_OEM_2]     = E2D_KEY_FORWARDSLASH;
    vk_to_e2d_lut[VK_OEM_5]     = E2D_KEY_BACKSLASH;     
    vk_to_e2d_lut[VK_OEM_7]     = E2D_KEY_APOSTROPHE;     
    vk_to_e2d_lut[VK_OEM_1]     = E2D_KEY_SEMICOLON;
        
    // assign alphabet
    vk_map_sequence_e2d(0x41, E2D_KEY_A, 26);

    // assign numbers
    vk_map_sequence_e2d(0x30, E2D_KEY_0, 10);
    
    // assign numpad
    vk_map_sequence_e2d(VK_NUMPAD0, E2D_KEY_NUM0, 10);
    
    // assign f-keys
    vk_map_sequence_e2d(VK_F1, E2D_KEY_F1, 12);    
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // identify which window called the window procedure
    char class_name[5];
    GetClassName(hwnd, class_name, 5);
    int window_id = atoi(class_name);
    e2d_Window* window = windows[window_id];
    
    switch (uMsg)
    {
        case WM_DESTROY:
        case WM_CLOSE: {
            window->keep_running = false;
        } break;

        case WM_SIZE: {
            window->client_width = LOWORD(lParam);
            window->client_height = HIWORD(lParam);
            window->resolution_scale_width = (float)window->resolution_width / window->client_width;
            window->resolution_scale_height = (float)window->resolution_height / window->client_height;    
        } break;

        case WM_MOUSEMOVE: {
            window->mouse_x = LOWORD(lParam);
            window->mouse_y = HIWORD(lParam);
        } break;

        case WM_LBUTTONDOWN: {
            window->mouse_down_state[E2D_LMB] = true;
            window->mouse_pressed_state[E2D_LMB] = true;
        } break;
        
        case WM_LBUTTONUP: {
            window->mouse_down_state[E2D_LMB] = false;
            window->mouse_released_state[E2D_LMB] = true;
        } break;
        
        case WM_RBUTTONDOWN: {
            window->mouse_down_state[E2D_RMB] = true;
            window->mouse_pressed_state[E2D_RMB] = true;
        } break;

        case WM_RBUTTONUP: {
            window->mouse_down_state[E2D_RMB] = false;
            window->mouse_released_state[E2D_RMB] = true;
        } break;
        
        case WM_MBUTTONDOWN: {
            window->mouse_down_state[E2D_MMB] = true;
            window->mouse_pressed_state[E2D_MMB] = true;
        } break;

        case WM_MBUTTONUP: {
            window->mouse_down_state[E2D_MMB] = false;
            window->mouse_released_state[E2D_MMB] = true;
        } break;

        case WM_MOUSEWHEEL: {
            window->mouse_wheel_delta += GET_WHEEL_DELTA_WPARAM(wParam) / 120;
        } break;

        case WM_KEYDOWN: {
            e2d_Key key = vk_to_e2d_lut[wParam];
            window->key_down_state[key] = true;
            window->key_pressed_state[key] = true;
        } break;

        case WM_KEYUP: {
            e2d_Key key = vk_to_e2d_lut[wParam];
            window->key_released_state[key] = true;
            window->key_down_state[key] = false;
        } break;
        
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

void e2d_handle_events()
{
    // reset at start of each frame
    for (int i = 0; i < window_count; i++)
    {
        memset(windows[i]->mouse_pressed_state,  0, E2D_MOUSEBUTTON_COUNT * sizeof(bool));
        memset(windows[i]->mouse_released_state, 0, E2D_MOUSEBUTTON_COUNT * sizeof(bool));

        memset(windows[i]->key_pressed_state,  0, E2D_KEY_COUNT * sizeof(bool));
        memset(windows[i]->key_released_state, 0, E2D_KEY_COUNT * sizeof(bool));
                
        windows[i]->mouse_wheel_delta = 0;
    }

    MSG message = { 0 };
    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

int e2d_get_mouse_x(e2d_Window* window)
{
    return window->mouse_x;
}

int e2d_get_mouse_y(e2d_Window* window)
{
    return window->mouse_y;
}

int e2d_get_mouse_x_in_framebuffer(e2d_Window* window)
{
    return window->mouse_x * window->resolution_scale_width;    
}

int e2d_get_mouse_y_in_framebuffer(e2d_Window* window)
{
    return window->mouse_y * window->resolution_scale_height;        
}

int e2d_get_mouse_wheel_delta(e2d_Window* window)
{
    return window->mouse_wheel_delta;
}

bool e2d_is_mouse_down(e2d_Window* window, e2d_MouseButton mouse_button)
{
    return window->mouse_down_state[mouse_button];
}

bool e2d_is_mouse_pressed(e2d_Window* window, e2d_MouseButton mouse_button)
{
    return window->mouse_pressed_state[mouse_button];
}

bool e2d_is_mouse_released(e2d_Window* window, e2d_MouseButton mouse_button)
{
    return window->mouse_released_state[mouse_button];
}

bool e2d_is_key_down(e2d_Window* window, e2d_Key key)
{
    return window->key_down_state[key];
}

bool e2d_is_key_pressed(e2d_Window* window, e2d_Key key)
{
    return window->key_pressed_state[key];
}

bool e2d_is_key_released(e2d_Window* window, e2d_Key key)
{
    return window->key_released_state[key];
}
