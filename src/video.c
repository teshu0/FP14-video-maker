#include <stdio.h>
#include <stdbool.h>

#include "video.h"
#include "image.h"

Layer *new_layer(Sprite *sprite, unsigned int x, unsigned int y, bool should_clip, void (*callback)(int frame, unsigned int *x, unsigned int *y))
{
    Layer *layer = malloc(sizeof(Layer));
    layer->sprite = sprite;
    layer->x = x;
    layer->y = y;
    layer->should_clip = should_clip;
    layer->render_callback = callback;
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

RGBImage *render_scene(Scene *scene, unsigned int current_frame, uint32_t background_color)
{
    // レンダリング用の画像を確保
    RGBImage *scene_image = new_rgb_image(scene->width, scene->height);

    for (int y = 0; y < scene->height; y++)
    {
        for (int x = 0; x < scene->width; x++)
        {
            // RGB のみを持つ
            scene_image->pixels[y][x] = *new_rgb_pixel(background_color); // default is black
        }
    }

    for (int layer_index = 0; layer_index < scene->num_layers; layer_index++)
    {
        // 下の方からレイヤーを取得
        Layer *layer = scene->layers[layer_index];
        unsigned int offset_x = layer->x;
        unsigned int offset_y = layer->y;
        Sprite *sprite = layer->sprite;
        unsigned int frame_index = current_frame % sprite->num_frames;

        for (int y = 0; y < sprite->images[frame_index]->height; y++)
        {
            if (y + offset_y >= scene->height) // || layer->should_clip
            {
                continue; // はみ出し
            }
            for (int x = 0; x < sprite->images[frame_index]->width; x++)
            {
                if (x + offset_x >= scene->width && layer->should_clip)
                {
                    continue; // はみ出し
                }
                int y_index = (y + offset_y) % scene->height;
                int x_index = (x + offset_x) % scene->width;

                Pixel pixel = sprite->images[frame_index]->pixels[y][x];
                if (pixel.hex == 0xFF000000 || get_alpha_rgba(&pixel) == 0x00) // completely transparent
                {
                    continue;
                }

                // 透明度を考慮して合成し RGB に変換?
                RGBPixel *rgb_pixel = get_alpha_applied_pixel(&pixel);

                // 加算合成
                scene_image->pixels[y_index][x_index].hex = rgb_pixel->hex;
            }
        }
    }

    return scene_image;
}

void renderling_loop(Scene *scene, unsigned int num_frames, char *output_path, uint32_t background_color)
{
    int num_layers = scene->num_layers;
    for (int current_frame = 0; current_frame < num_frames; current_frame++)
    {
        for (int layer_index = 0; layer_index < num_layers; layer_index++)
        {
            Layer *layer = scene->layers[layer_index];
            if (layer->render_callback != NULL)
            {
                layer->render_callback(current_frame, &layer->x, &layer->y);
            }
        }

        // レンダリング
        RGBImage *scene_image = render_scene(scene, current_frame, background_color);
        // 保存先のファイル名を作成
        char *filename = get_frame_filename(output_path, current_frame);
        save_image(scene_image, filename);
        // 解放
        free(scene_image);
    }
}

char *get_frame_filename(const char *parent_folder, unsigned int frame)
{
    char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "%s/frame_%05d.ppm", parent_folder, frame);
    return filename;
}