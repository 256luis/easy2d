#define WIN32_LEAN_AND_MEAN

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include "easy2d.h"

typedef struct e2d_Window
{
    int client_width;
    int client_height;
    int resolution_width;
    int resolution_height;
    float resolution_scale_width;
    float resolution_scale_height;
    uint32_t* framebuffer;
    HWND window_handle;
    bool keep_running;
    BITMAPINFO bitmap_info;
    HDC device_context;
    int mouse_x;
    int mouse_y;
} e2d_Window;

HINSTANCE hInstance;
PSTR pCmdLine;
int nCmdShow;

unsigned int window_count;
e2d_Window* windows[100];

static
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
            window->client_width = GET_X_LPARAM(lParam);
            window->client_height = GET_Y_LPARAM(lParam);
            window->resolution_scale_width = (float)window->resolution_width / window->client_width;
            window->resolution_scale_height = (float)window->resolution_height / window->client_height;    
        } break;

        case WM_MOUSEMOVE: {
            window->mouse_x = GET_X_LPARAM(lParam);
            window->mouse_y = GET_Y_LPARAM(lParam);
        } break;
            
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

// todo: this
void e2d_init()
{
    hInstance = GetModuleHandle(NULL);
    pCmdLine = GetCommandLine();
    nCmdShow = SW_SHOW;
    window_count = 0;
}

e2d_Window* e2d_create_window(int client_width, int client_height, int resolution_width, int resolution_height, const char* title)
{    
    // create the e2d_window
    e2d_Window* window = malloc(sizeof(e2d_Window));
    window->keep_running = true;
    window->client_width = client_width;
    window->client_height = client_height;
    window->resolution_width = resolution_width;
    window->resolution_height = resolution_height;
    window->resolution_scale_width = (float)resolution_width / client_width;
    window->resolution_scale_height = (float)resolution_height / client_height;
    
    // allocate framebuffer
    window->framebuffer = malloc(resolution_width * resolution_height * sizeof(uint32_t));

    // create window class
    char window_class_name[5];
    sprintf(window_class_name, "%d", window_count);
    WNDCLASS window_class = {
        .lpfnWndProc = WindowProc,
        .hInstance = hInstance,
        .lpszClassName = window_class_name
    };
    RegisterClass(&window_class);

    // get desired client rect
    RECT window_rect = {
        .right = client_width,
        .bottom = client_height
    };
    AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, false);
    int window_width = window_rect.right - window_rect.left; 
    int window_height = window_rect.bottom - window_rect.top;
    
    // create and show the window handle
    window->window_handle = CreateWindow(
        window_class.lpszClassName,        
        title,                  // window name
        WS_OVERLAPPEDWINDOW,                // style
        CW_USEDEFAULT, CW_USEDEFAULT,       // x and y postion
        window_width, window_height,
        NULL, NULL, 
        hInstance,
        NULL
    );

    // create device context
    window->device_context = GetDC(window->window_handle);

    // create bitmap info header to be put in window->bitmap_info
    BITMAPINFOHEADER bitmap_info_header = {
        .biSize = sizeof(BITMAPINFOHEADER),
        .biWidth = resolution_width,
        .biHeight = -resolution_height,
        .biPlanes = 1,
        .biBitCount = 32,
        .biCompression = BI_RGB
    };
    window->bitmap_info.bmiHeader = bitmap_info_header;
    
    windows[window_count] = window;
    window_count++;
    
    return window;
}

void e2d_destroy_window(e2d_Window* window)
{
    free(window->framebuffer);
    free(window);
}

void e2d_show_window(e2d_Window* window)
{
    ShowWindow(window->window_handle, nCmdShow);
}

bool e2d_should_window_close(e2d_Window* window)
{
    return !window->keep_running;
}

void e2d_handle_events()
{
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

void e2d_set_pixel(e2d_Window* window, int x, int y, uint32_t color)
{
    if (x < 0 || x >= window->resolution_width) return;
    if (y < 0 || y >= window->resolution_height) return;

    window->framebuffer[x + (y * window->resolution_width)] = color;
}

void e2d_clear_framebuffer(e2d_Window* window, uint32_t color)
{
    for (int i = 0; i < e2d_get_framebuffer_length(window); i++)
    {
        window->framebuffer[i] = color;
    }
}

uint32_t* e2d_get_framebuffer_reference(e2d_Window* window)
{
    return window->framebuffer;
}

int e2d_get_framebuffer_length(e2d_Window* window)
{
    return window->resolution_width * window->resolution_height;
}

void e2d_draw_framebuffer(e2d_Window* window)
{
    StretchDIBits(
        window->device_context,     // hdc
        0, 0,                       // xDest, yDest
        window->client_width,       // DestWidth
        window->client_height,      // DestWidth
        0, 0,                       // xSrc, ySrc
        window->resolution_width,   // SrcWidth
        window->resolution_height,  // SrcHeight
        window->framebuffer,                // lpBits
        &window->bitmap_info,       // lpBmi
        DIB_RGB_COLORS,             // iUsage
        SRCCOPY
    );
}
