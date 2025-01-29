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
    pixel->hex = 0x00000000;
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
    for (int y = 0; y < height; y++)
    {
        pixels[y] = malloc(sizeof(Pixel) * width);

        for (int x = 0; x < width; x++)
        {
            pixels[y][x] = *new_empty_pixel();
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

void _init_rgb_image(RGBImage *image, unsigned int width, unsigned int height)
{
    // init with 0x00000000
    RGBPixel **pixels = malloc(sizeof(RGBPixel) * width * height);
    for (int y = 0; y < height; y++)
    {
        pixels[y] = malloc(sizeof(RGBPixel) * width);

        for (int x = 0; x < width; x++)
        {
            pixels[y][x] = *new_rgb_pixel(0x000000);
        }
    }

    image->width = width;
    image->height = height;
    image->pixels = pixels;
}

RGBImage *new_rgb_image(unsigned int width, unsigned int height)
{
    RGBImage *image = malloc(sizeof(RGBImage));
    _init_rgb_image(image, width, height);

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

void save_image(RGBImage *image, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "can't open %s\n", filename);
        exit(1);
    }

    // file width, height, and max color value
    fprintf(file, "P6\n%d %d\n255\n", image->width, image->height);

    unsigned int width = image->width;
    unsigned int height = image->height;

    unsigned char *pixels = malloc(sizeof(unsigned char) * width * height * 3); // 3 for rgb
    for (int y = 0; y < image->height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            pixels[(y * width + x) * 3] = get_red_rgb(&image->pixels[y][x]);
            pixels[(y * width + x) * 3 + 1] = get_green_rgb(&image->pixels[y][x]);
            pixels[(y * width + x) * 3 + 2] = get_blue_rgb(&image->pixels[y][x]);
        }
    }

    // PPM format
    fwrite(pixels, sizeof(unsigned char), image->width * image->height * 3, file);

    fclose(file);
}

// Pixel

uint32_t get_alpha_rgba(Pixel *pixel)
{
    return (pixel->hex & 0xff000000) >> 24;
}

uint32_t get_blue_rgba(Pixel *pixel)
{
    return (pixel->hex & 0x00ff0000) >> 16;
}

uint32_t get_green_rgba(Pixel *pixel)
{
    return (pixel->hex & 0x0000ff00) >> 8;
}

uint32_t get_red_rgba(Pixel *pixel)
{
    return (pixel->hex & 0x000000ff);
}

// RGBPixel
uint32_t get_red_rgb(RGBPixel *pixel)
{
    return (pixel->hex & 0xff0000) >> 16;
}

uint32_t get_green_rgb(RGBPixel *pixel)
{
    return (pixel->hex & 0x00ff00) >> 8;
}

uint32_t get_blue_rgb(RGBPixel *pixel)
{
    return (pixel->hex & 0x0000ff);
}

RGBPixel *new_rgb_pixel(uint32_t hex)
{
    RGBPixel *rgb = malloc(sizeof(RGBPixel));
    rgb->hex = hex;
    return rgb;
}

RGBPixel *get_alpha_applied_pixel(Pixel *pixel)
{
    RGBPixel *rgb = malloc(sizeof(RGBPixel));
    double alpha = (double)get_alpha_rgba(pixel) / 255.0;
    unsigned int red = (unsigned int)(get_red_rgba(pixel) * alpha);
    unsigned int green = (unsigned int)(get_green_rgba(pixel) * alpha);
    unsigned int blue = (unsigned int)(get_blue_rgba(pixel) * alpha);

    rgb->hex = (red << 16) | (green << 8) | blue;

    return rgb;
}

RGBPixel *add_rgb_pixel(RGBPixel *left, Pixel *right)
{
    uint32_t red_left = get_red_rgb(left);
    uint32_t blue_left = get_blue_rgb(left);
    uint32_t green_left = get_green_rgb(left);

    double alpha_right = (double)get_alpha_rgba(right) / 255.0;
    uint32_t red_right = get_red_rgba(right) * alpha_right;
    uint32_t blue_right = get_blue_rgba(right) * alpha_right;
    uint32_t green_right = get_green_rgba(right) * alpha_right;

    double alpha_sum = 1 + alpha_right;

    uint32_t red = ((red_left + red_right) > 255 ? 255 : (red_left + red_right));
    uint32_t blue = ((blue_left + blue_right) > 255 ? 255 : (blue_left + blue_right));
    uint32_t green = ((green_left + green_right) > 255 ? 255 : (green_left + green_right));

    return new_rgb_pixel(
        (red << 16) + (blue << 8) + green);
}

RGBImage *convert_to_rgb_image(Image *image, uint32_t background_color)
{
    RGBImage *rgb_image = new_rgb_image(image->width, image->height);

    for (int y = 0; y < image->height; y++)
    {
        for (int x = 0; x < image->width; x++)
        {
            Pixel pixel = image->pixels[y][x];
            if (pixel.hex == 0x00000000)
            {
                rgb_image->pixels[y][x] = *new_rgb_pixel(background_color);
            }
            else
            {
                RGBPixel *rgb_pixel = get_alpha_applied_pixel(&pixel);
                rgb_image->pixels[y][x] = *rgb_pixel;
            }
        }
    }

    return rgb_image;
}
