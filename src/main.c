#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// #include "array.h"
#include "image.h"
#include "sprite.h"
#include "video.h"

#define OUTPUT_PATH = "./output"

void move_kirby(int frame, unsigned int *x, unsigned int *y)
{
    *x += 4;
    // *y += 4;
}

int main()
{

    Sprite *debug_1 = new_debug_horizontal();
    Sprite *debug_2 = new_debug_square();

    Sprite *kirby = new_kirby_sprite();
    Sprite *cloud = new_cloud_sprite();

    Layer *layer_debug_1 = new_layer(debug_1, 0, 0, NULL);
    Layer *layer_debug_2 = new_layer(debug_2, 0, 0, NULL);
    Layer *layer_kirby = new_layer(kirby, 16, 16, *move_kirby);
    Layer *layer_cloud = new_layer(cloud, -100, 0, NULL);

    Scene *scene = new_scene(64, 64);
    // add_layer(scene, layer_debug_1);
    add_layer(scene, layer_debug_2);
    add_layer(scene, layer_kirby);
    // add_layer(scene, layer_cloud);

    renderling_loop(scene, 10, "./output", 0xF0F0F0);

    return 0;
}