#include <stdio.h>
#include <stdlib.h>
#include "easy2d_internals.h"

HINSTANCE hInstance;
PSTR pCmdLine;
int nCmdShow;

unsigned int window_count;
e2d_Window* windows[100];

void e2d_init()
{
    hInstance = GetModuleHandle(NULL);
    pCmdLine = GetCommandLine();
    nCmdShow = SW_SHOW;
    window_count = 0;

    internal_time_init();
    vk_to_e2d_lut_init();
}

void e2d_close()
{
    timeEndPeriod(1);
}

e2d_Window* e2d_window_create(int width, int height, const char* title)
{
    // create the e2d_window
    e2d_Window* window = calloc(1, sizeof(e2d_Window));
    window->keep_running = true;
    window->width = width;
    window->height = height;

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
        .right = width,
        .bottom = height
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

void e2d_window_set_title(e2d_Window* window, const char* title)
{
    SetWindowText(window->window_handle, title);
}

void e2d_window_destroy(e2d_Window* window)
{
    DestroyWindow(window->window_handle);
    free(window);
}

bool e2d_window_should_close(e2d_Window* window)
{
    return !window->keep_running;
}
