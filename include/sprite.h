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
Sprite *new_debug_square();
Sprite *new_debug_horizontal();
Sprite *new_debug_animated();

/// @brief カービィのスプライトを取得
/// @return
Sprite *new_kirby_sprite();

/// @brief 雲のスプライトを取得
/// @return
Sprite *new_cloud_sprite();

/// @brief 背景のスプライト
/// @return
Sprite *new_background_sprite();

/// @brief 床のスプライト
/// @return
Sprite *new_floor_sprite();

#endif // SPRITE_H