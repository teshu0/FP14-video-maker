// 動画に関する定義

#ifndef VIDEO_H
#define VIDEO_H

#include "image.h"
#include "sprite.h"

/// @brief スプライトとその位置をもつレイヤー
typedef struct
{
    Sprite *sprite;
    unsigned int x;
    unsigned int y;
} Layer;

/// @brief 初期位置を含めて新しいレイヤーを作成する
/// @param sprite
/// @param x
/// @param y
/// @return
Layer *new_layer(Sprite *sprite, unsigned int x, unsigned int y);

/// @brief レイヤーの配列をもつシーン
typedef struct
{
    Layer **layers;
    unsigned int width;
    unsigned int height;
    unsigned int num_layers;
} Scene;

/// @brief 新しいシーンを作成する
/// @param width
/// @param height
/// @return
Scene *new_scene(unsigned int width, unsigned int height);

/// @brief レイヤーを追加する
/// @param scene
/// @param layer
void add_layer(Scene *scene, Layer *layer);

/// @brief シーンをレンダリングする
/// @param scene
/// @param current_frame 現在のフレーム (1~)
/// @return
RGBImage *render_scene(Scene *scene, unsigned int current_frame);

#endif // VIDEO_H