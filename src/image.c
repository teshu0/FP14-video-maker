#include <stdio.h>

#include "image.h"

// RGB に関する実装

RGB *new_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
    RGB *color = malloc(sizeof(RGB));
    color->red = red;
    color->green = green;
    color->blue = blue;

    return color;
}

RGB *new_black_color()
{
    RGB *color = malloc(sizeof(RGB));
    color->red = 0;
    color->green = 0;
    color->blue = 0;

    return color;
}

Pixel *new_pixel(unsigned char red, unsigned char green, unsigned char blue, float alpha)
{
    Pixel *pixel = malloc(sizeof(Pixel));
    RGB *color = new_rgb(red, green, blue);

    pixel->color = color;
    pixel->alpha = alpha;

    return pixel;
}

Pixel *new_black_pixel()
{
    Pixel *pixel = malloc(sizeof(Pixel));
    RGB *color = new_black_color();

    pixel->color = color;
    pixel->alpha = 100.0;

    return pixel;
}

// ピクセルに関する実装

void print_pixel_hex(Pixel *pixel)
{
    printf("#%02x%02x%02x (%.02f)\n", pixel->color->red, pixel->color->green, pixel->color->blue, pixel->alpha);
}

// 画像に関する実装

void _init_image(Image *image, unsigned int width, unsigned int height)
{
    Pixel **pixels = malloc(sizeof(Pixel) * width);
    for (int i = 0; i < width; i++)
    {
        pixels[i] = malloc(sizeof(Pixel) * height);

        for (int j = 0; j < height; j++)
        {
            pixels[i][j] = *new_black_pixel();
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
            pixels[(i * image->width + j) * 3] = image->pixels[j][i].color->red;
            pixels[(i * image->width + j) * 3 + 1] = image->pixels[j][i].color->green;
            pixels[(i * image->width + j) * 3 + 2] = image->pixels[j][i].color->blue;
        }
    }

    // PPM format
    fwrite(pixels, sizeof(unsigned char), image->width * image->height * 3, file);

    fclose(file);
}