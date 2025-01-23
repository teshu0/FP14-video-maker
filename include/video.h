// 動画に関する定義

#include "image.h"

// スプライト (画像の管理)
typedef struct
{
    /// @brief 画像の配列で、フレームごとにアニメーションできる可能性がある
    Image *image;
} Sprite;

// レイヤー (スプライトの管理)
typedef struct
{
    Sprite *sprite;

    unsigned int x;
    unsigned int y;

    double scale;

} Layer;

// フレーム (レイヤーの集合)
typedef struct
{
    Layer **layers;
} Frame;

// シーン (フレームの集合)
typedef struct
{
    Frame **frames;
} Scene;