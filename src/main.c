#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "image.h"
#include "sprite.h"
#include "video.h"

#define OUTPUT_PATH = "./output"

void move_kirby_forward(int frame, unsigned int *x, unsigned int *y)
{
    *x += 2;
}

void move_background_backward(int frame, unsigned int *x, unsigned int *y)
{
    *x -= 1;
}

void move_cloud_backward(int frame, unsigned int *x, unsigned int *y)
{
    if (frame % 4 == 0)
    {
        // 左に
        *x -= 1;

        // 上下に
        if (frame % 8 == 0)
        {
            *y -= 1;
        }
        else
        {
            *y += 1;
        }
    }
}

void move_floor_backward(int frame, unsigned int *x, unsigned int *y)
{
    if (frame % 2 == 0)
    {
        // 左に
        *x -= 1;
    }
}

int main()
{

    // Sprite *debug_1 = new_debug_horizontal();
    Sprite *debug_2 = new_debug_square();

    Sprite *kirby = new_kirby_sprite();
    Sprite *cloud = new_cloud_sprite();
    Sprite *background = new_background_sprite();
    Sprite *floor = new_floor_sprite();

    // Layer *layer_debug_1 = new_layer(debug_1, 0, 0, false, NULL);
    Layer *layer_debug_2 = new_layer(debug_2, 0, 0, false, NULL);
    Layer *layer_kirby = new_layer(kirby, 16, 100 - 16, false, move_kirby_forward);
    Layer *layer_cloud = new_layer(cloud, -40, -20, false, move_cloud_backward);
    Layer *layer_background = new_layer(background, 0, 0, false, move_background_backward);
    Layer *layer_floor = new_layer(floor, 0, 100, false, move_floor_backward);

    Scene *scene = new_scene(240, 160);
    // add_layer(scene, layer_debug_1);
    add_layer(scene, layer_background);
    add_layer(scene, layer_floor);
    add_layer(scene, layer_kirby);
    add_layer(scene, layer_cloud);
    add_layer(scene, layer_debug_2);

    renderling_loop(scene, 24 * 10, "./output", 0xF0F0F0);

    return 0;
}