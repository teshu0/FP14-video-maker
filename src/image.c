#include <stdio.h>

#include "image.h"

Pixel *new_pixel(uint32_t hex)
{
    Pixel *pixel = malloc(sizeof(Pixel));
    pixel->hex = hex;
    return pixel;
}

Pixel *new_empty_pixel()
{
    Pixel *pixel = malloc(sizeof(Pixel));

    pixel->hex = 0xff000000;

    return pixel;
}

// ピクセルに関する実装

void print_pixel_hex(Pixel *pixel)
{

    printf("#%02x%02x%02x%02x\n",
           (pixel->hex & 0xff000000) >> 24,
           (pixel->hex & 0x00ff0000) >> 16,
           (pixel->hex & 0x0000ff00) >> 8,
           (pixel->hex & 0x000000ff));
}

// 画像に関する実装

void _init_image(Image *image, unsigned int width, unsigned int height)
{
    // init with 0x00000000
    Pixel **pixels = malloc(sizeof(Pixel) * width * height);
    for (int i = 0; i < width; i++)
    {
        pixels[i] = malloc(sizeof(Pixel) * height);

        for (int j = 0; j < height; j++)
        {
            pixels[i][j] = *new_empty_pixel();
        }
    }

    image->width = width;
    image->height = height;
    image->pixels = pixels;
}

Image *new_image(unsigned int width, unsigned int height)
{
    Image *image = malloc(sizeof(Image));
    _init_image(image, width, height);
    return image;
}

void set_pixel(Image *image, unsigned int x, unsigned int y, Pixel *pixel)
{
    if (x >= image->width || y >= image->height)
    {
        fprintf(stderr, "index out of range\n");
        exit(1);
    }

    image->pixels[x][y] = *pixel;
}

void save_image(Image *image, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "can't open %s\n", filename);
        exit(1);
    }

    // file width, height, and max color value
    fprintf(file, "P6\n%d %d\n255\n", image->width, image->height);

    unsigned char *pixels = malloc(sizeof(unsigned char) * image->width * image->height * 3); // 3 for rgb
    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            pixels[(i * image->width + j) * 3] = get_red(&image->pixels[j][i]);
            pixels[(i * image->width + j) * 3 + 1] = get_green(&image->pixels[j][i]);
            pixels[(i * image->width + j) * 3 + 2] = get_blue(&image->pixels[j][i]);
        }
    }

    // PPM format
    fwrite(pixels, sizeof(unsigned char), image->width * image->height * 3, file);

    fclose(file);
}

uint32_t get_red(Pixel *pixel)
{
    return (pixel->hex & 0x00ff0000) >> 16;
}

uint32_t get_green(Pixel *pixel)
{
    return (pixel->hex & 0x0000ff00) >> 8;
}

uint32_t get_blue(Pixel *pixel)
{
    return (pixel->hex & 0x000000ff);
}

uint32_t get_alpha(Pixel *pixel)
{
    return (pixel->hex & 0xff000000) >> 24;
}