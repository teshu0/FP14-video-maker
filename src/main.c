#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "image.h"

int main()
{
    Image *image = new_image(64, 64);

    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
        {
            // set random pixel
            Pixel *pixel = new_pixel(
                rand() % 256,
                rand() % 256,
                rand() % 256,
                100.0);
            if (i == j)
            {
                pixel->color->blue = 255;
            }
            set_pixel(image, j, i, pixel);
        }
    }

    save_image(image, "output.ppm");

    return 0;
}