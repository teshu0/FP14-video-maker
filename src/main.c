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
                // random color
                (rand() % 0xff << 24) |
                (rand() % 0xff << 16) |
                (rand() % 0xff << 8) |
                (rand() % 0xff));
            if (i == j)
            {
                // set blue part 0xff
                pixel->hex = pixel->hex | 0x000000ff;
            }
            set_pixel(image, j, i, pixel);
        }
    }

    save_image(image, "output.ppm");

    return 0;
}