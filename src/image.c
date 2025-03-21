#define STB_IMAGE_IMPLEMENTATION

#include <stdint.h>
#include "easy2d.h"
#include "stb_image.h"

e2d_Texture* e2d_texture_load(const char* path)
{
    e2d_Texture* texture = malloc(sizeof(e2d_Texture));
    if (texture == NULL) return NULL;

    int comp;
    uint8_t* image_data = stbi_load(path, &texture->width, &texture->height, &comp, 4);
    if (image_data == NULL) return NULL;

    // structure of image_data
    // image_data[0] = red component
    // image_data[1] = blue component
    // image_data[2] = green component
    // image_data[3] = alpha component
    // image_data[4] = red component
    // ...

    texture->pixels = malloc(sizeof(e2d_Color) * texture->width * texture->height);

    for (int i = 0, j = 0; j < texture->width * texture->height; i += 4, j++)
    {
        texture->pixels[j].r = image_data[i];
        texture->pixels[j].g = image_data[i + 1];
        texture->pixels[j].b = image_data[i + 2];
        texture->pixels[j].a = image_data[i + 3];
    }

    stbi_image_free(image_data);

    return texture;
}

void e2d_texture_destroy(e2d_Texture* texture)
{
    free(texture->pixels);
    free(texture);
}

void e2d_texture_copy_to_texture(e2d_Texture* source_texture,
                                 int source_x, int source_y,
                                 int source_width, int source_height,
                                 e2d_Texture* destination_texture,
                                 int destination_x, int destination_y,
                                 int destination_width, int destination_height)
{
    for (int x = 0; x < source_width; x++)
    {
        for (int y = 0; y < source_height; y++)
        {
            int sampled_x = (x + source_x) % source_texture->width;
            int sampled_y = (y + source_y) % source_texture->height;
            e2d_Color sampled_color = source_texture->pixels[sampled_x + (sampled_y * source_texture->width)];
            e2d_texture_set_pixel(destination_texture, destination_x + x, destination_y + y, sampled_color);
        }
    }
}
