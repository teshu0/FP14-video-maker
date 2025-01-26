#include "video.h"
#include "image.h"

Layer *new_layer(Sprite *sprite, unsigned int x, unsigned int y)
{
    Layer *layer = malloc(sizeof(Layer));
    layer->sprite = sprite;
    layer->x = x;
    layer->y = y;
    return layer;
}

Scene *new_scene(unsigned int width, unsigned int height)
{
    Scene *scene = malloc(sizeof(Scene));
    scene->layers = malloc(sizeof(Layer *) * width * height);
    scene->width = width;
    scene->height = height;
    scene->num_layers = 0;
    return scene;
}

void add_layer(Scene *scene, Layer *layer)
{
    scene->layers[scene->num_layers] = layer;
    scene->num_layers++;
}

RGBImage *render_scene(Scene *scene, unsigned int current_frame)
{
    RGBImage *scene_image = malloc(sizeof(RGBImage));
    scene_image->width = scene->width;
    scene_image->height = scene->height;
    // 縦横サイズのメモリ確保
    scene_image->pixels = malloc(sizeof(uint32_t *) * scene->width * scene->height);

    for (int y = 0; y < scene->height; y++)
    {
        for (int x = 0; x < scene->width; x++)
        {
            // RGB のみを持つ
            scene_image->pixels[y][x] = *new_rgb_pixel(0x000000); // default is black
        }
    }

    for (int i = 0; i < scene->num_layers; i++)
    {
        // 下の方からレイヤーを取得
        Layer *layer = scene->layers[i];
        unsigned int offset_x = layer->x;
        unsigned int offset_y = layer->y;
        Sprite *sprite = layer->sprite;
        unsigned int frame_index = current_frame % sprite->num_frames;

        for (int y = 0; y < sprite->images[frame_index]->height; y++)
        {
            for (int x = 0; x < sprite->images[frame_index]->width; x++)
            {
                Pixel pixel = sprite->images[frame_index]->pixels[y][x];
                if (pixel.hex != 0xff000000)
                {
                    // 透明度を考慮して合成し RGB に変換
                    RGBPixel *rgb_pixel = get_alpha_applied_pixel(&pixel);

                    // 加算合成
                    scene_image->pixels[y + offset_y][x + offset_x].hex += rgb_pixel->hex;
                }
            }
        }
    }

    return scene_image;
}