#include <stdio.h>
#include <stdint.h>

#include "sprite.h"
#include "image.h"

Sprite *new_sprite(
    uint32_t **hex,
    unsigned int frames,
    unsigned int width,
    unsigned int height)

{
    Image **images = malloc(sizeof(Image *) * frames);
    for (int i = 0; i < frames; i++)
    {
        images[i] = new_image(width, height);
    }

    // 2 of 32x32 images
    for (int frame = 0; frame < frames; frame++)
    {
        printf("frame: %d\n", frame);
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                images[frame]->pixels[y][x] = *new_pixel(hex[frame][y * width + x]);
            }
        }
    }

    Sprite *sprite = malloc(sizeof(images));
    sprite->images = images;
    sprite->num_frames = frames;

    return sprite;
}