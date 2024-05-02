// TODO: support JPEG, PNG

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>
#include "easy2d.h"
#include "easy2d_internals.h"

#define E2D_ASSERT(condition, if_false) if (!(condition)) return if_false
#define E2D_REINTERPRET_CAST(var, new_type) (*((new_type*)&(var)))
    
// bitmap file header
// byte 0x00 - 0x01 (2 bytes) -- MUST BE 0x42 0x4D
// byte 0x02 - 0x05 (4 bytes) -- size of bmp file in bytes
// byte 0x06 - 0x09 (4 bytes) -- dont care
// byte 0x0A - 0x0D (4 bytes) -- starting address of pixel array

// bitmap info header size (determines which bitmap info header is used)
// byte 0x0E - 0x11 (4 bytes) -- size of header

// 40 bytes - BITMAPINFOHEADER
// byte 0x12 - 0x15 (4 bytes) -- width as signed int
// byte 0x16 - 0x19 (4 bytes) -- height as signed int
// byte 0x1A - 0x1B (2 bytes) -- number of color planes (must be 1)
// byte 0x1C - 0x1D (2 bytes) -- number of bits per pixel
// byte 0x1E - 0x21 (4 bytes) -- compression method
// byte 0x22 - 0x35 (20 bytes) - dont care

e2d_Image* e2d_parse_bmp(uint8_t* bytes)
{
    // validate signature
    E2D_ASSERT(bytes[0x00] == 0x42 && bytes[0x01] == 0x4D, NULL);

    uint32_t pixels_start = E2D_REINTERPRET_CAST(bytes[0x0A], uint32_t);    
    int32_t width = E2D_REINTERPRET_CAST(bytes[0x12], int32_t);
    int32_t height = E2D_REINTERPRET_CAST(bytes[0x16], int32_t);
    uint16_t planes = E2D_REINTERPRET_CAST(bytes[0x1A], uint16_t);        
    E2D_ASSERT(planes == 1, NULL);
    uint16_t bit_count = E2D_REINTERPRET_CAST(bytes[0x1C], uint16_t);

    e2d_Image* image = malloc(sizeof(e2d_Image));
    image->width = width;
    image->height = height;
                        
    int image_size = width * height;
    uint32_t* pixels_temp = calloc(image_size, sizeof(uint32_t));

    // copy pixel array from file to pixels_temp array
    // take into account different sized pixels
    if (bit_count >= 8)
    {
        int bytes_per_pixel = bit_count / 8;
        for (int i = 0, j = 0; i < image_size * 4; i += 4, j += bytes_per_pixel)
        {
            for (int k = 0; k < bytes_per_pixel; k++)
            {
                uint8_t* p = (uint8_t*)pixels_temp;
                p[i + k] = bytes[pixels_start + j + k];
            }
        }        
    }
    else
    {
        // TODO: this (read the BMP file format documentation)
        
    }
            
    // flip the image vertically
    image->pixels = calloc(image_size, sizeof(uint32_t));
    for (int old_y = height-1, new_y = 0; new_y < height; old_y--, new_y++)
    {
        for (int x = 0; x < width; x++)
        {
            image->pixels[x + (new_y * width)] = pixels_temp[x + (old_y * width)];
        }
    }
    
    free(pixels_temp);            
    return image;
}

e2d_Image* e2d_load_image(const char* path, e2d_ImageFormat image_format)
{
    // read file to array of bytes
    uint8_t* bytes;
    {
        FILE* file = fopen(path, "rb");
        if (file == NULL) return NULL;
        
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        bytes = malloc(sizeof(uint8_t) * size);
        if (bytes == NULL) return NULL;
        
        fread(bytes, 1, size, file);
        fclose(file);
    }
    
    e2d_Image* image;
    
    switch (image_format)
    {
        case E2D_BMP: image = e2d_parse_bmp(bytes); break;
        default: image = NULL;
    }

    free(bytes);
    return image;
}

// if `colors` is NULL, create empty image with `width` and `height` as initial dimensions
e2d_Image* e2d_create_image(e2d_Color* colors, int width, int height)
{
    E2D_ASSERT(width >= 0, NULL);
    E2D_ASSERT(height >= 0, NULL);

    e2d_Image* image = calloc(width * height, sizeof(e2d_Image));
    image->width = width;
    image->height = height;

    if (colors != NULL)
    {
        for (int i = 0; i < width * height; i++)
        {
            image->pixels[i] = colors[i].hex;
        }
    }
    
    return image;
}

void e2d_destroy_image(e2d_Image* image)
{
    free(image->pixels);
    free(image);
}
