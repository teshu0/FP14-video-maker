// 画像の管理に関する実装の定義

#ifndef IMAGE_H
#define IMAGE_H

#include "array.h"

/// @brief RGB値を表す構造体
typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

/// @brief RGB を作成してポインターを返す
/// @param red
/// @param green
/// @param blue
/// @return
RGB *new_rgb(unsigned char red, unsigned char green, unsigned char blue);

/// @brief 黒を取得する
/// @param color
RGB *new_black_color();

/// @brief ピクセルを表す構造体で、色と透明度をもつ
typedef struct
{
    RGB *color;
    /// @brief 透明度を0から100で表す。0が完全透明、100が完全不透明
    float alpha;
} Pixel;

/// @brief 新しいピクセルを作成し、ポインターを返す
/// @param red
/// @param green
/// @param blue
/// @param alpha
/// @return
Pixel *new_pixel(unsigned char red, unsigned char green, unsigned char blue, float alpha);

/// @brief 不透明な黒のピクセルを取得
/// @param pixel
Pixel *new_black_pixel();

/// @brief ピクセルをRGB値としてプリントする
/// @param pixel ピクセル
void print_pixel_hex(Pixel *pixel);

/// @brief 画像を表す構造体で、幅、高さ、ピクセルデータをもつ
typedef struct
{
    unsigned int width;
    unsigned int height;
    Pixel **pixels;
} Image;

/// @brief 画像を初期化する
/// @param image 画像
/// @param width 幅
/// @param height 高さ
void _init_image(Image *image, unsigned int width, unsigned int height);

/// @brief 新しい画像を作成する
/// @param width
/// @param height
/// @return
Image *new_image(unsigned int width, unsigned int height);

/// @brief 画像にピクセルをセットする
/// @param image
/// @param x
/// @param y
/// @param pixel
void set_pixel(Image *image, unsigned int x, unsigned int y, Pixel *pixel);

/// @brief 画像を保存する関数
/// @param image
/// @param filename 保存パス
void save_image(Image *image, const char *filename);

#endif // IMAGE_H