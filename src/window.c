#include <stdio.h>
#include <stdlib.h>
#include "easy2d_internals.h"

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
            window->client_width = LOWORD(lParam);
            window->client_height = HIWORD(lParam);
            window->resolution_scale_width = (float)window->resolution_width / window->client_width;
            window->resolution_scale_height = (float)window->resolution_height / window->client_height;    
        } break;

        case WM_MOUSEMOVE: {
            window->mouse_x = LOWORD(lParam);
            window->mouse_y = HIWORD(lParam);
        } break;
            
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

void e2d_init()
{
    hInstance = GetModuleHandle(NULL);
    pCmdLine = GetCommandLine();
    nCmdShow = SW_SHOW;
    window_count = 0;

    internal_time_init();
}

void e2d_close()
{
    timeEndPeriod(1);
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

    ShowWindow(window->window_handle, nCmdShow);
    
    return window;
}

void e2d_destroy_window(e2d_Window* window)
{
    free(window->framebuffer);
    free(window);
}

bool e2d_should_window_close(e2d_Window* window)
{
    return !window->keep_running;
}

