// 必要になるスプライトの定義

#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>
#include "image.h"

// スプライト (画像の管理)
typedef struct
{
    /// @brief 画像の配列で、フレームごとにアニメーションできる可能性がある
    Image **images;
    unsigned int num_frames;
} Sprite;

Sprite *new_sprite(
    uint32_t **hex,
    unsigned int frames,
    unsigned int width,
    unsigned int height);

// テスト用
Sprite *new_debug_object();
Sprite *new_debug_object_animated();

#endif // SPRITE_H