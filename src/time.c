#include <stdio.h>
#include <stdint.h>
#include <windows.h>

int performance_frequency;
double frame_start;
double target_delta_time;

double time_now;
double time_prev;
double delta_time;

void internal_time_init()
{
    timeBeginPeriod(1);
    
    // get performance frequency
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    performance_frequency =  freq.QuadPart;
}

double e2d_get_time()
{
    LARGE_INTEGER result;
    QueryPerformanceCounter(&result);
    return result.QuadPart / (double)performance_frequency;
}

void e2d_set_target_framerate(int target_framerate)
{
    target_delta_time =  (1000.0 / target_framerate) / 1000;
    time_now = e2d_get_time() - target_delta_time;
}

void e2d_update_time()
{
    frame_start = e2d_get_time();
    time_prev = time_now;
    time_now = frame_start;
    delta_time = time_now - time_prev;
}

void e2d_limit_framerate()
{
    double frame_time = e2d_get_time() - frame_start;
    if (frame_time < target_delta_time)
    {
        int amount_to_sleep = (target_delta_time - frame_time) * 1000;
        Sleep(amount_to_sleep);
    }
}

double e2d_get_delta_time()
{
    return delta_time;
}
