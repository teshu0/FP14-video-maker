// 画像の管理に関する実装の定義

#ifndef IMAGE_H
#define IMAGE_H

#include "array.h"

/// @brief ピクセルを表す構造体で、色と透明度をもつ
typedef struct
{
    // RGB+alpha の16進数
    uint32_t hex;
} Pixel;

/// @brief 新しいピクセルを作成し、ポインターを返す
/// @param uint32_t 16進数の色
/// @return
Pixel *new_pixel(uint32_t hex);

/// @brief ゼロのピクセルを取得
/// @param pixel
Pixel *new_empty_pixel();

// カラーの取得
uint32_t get_red(Pixel *pixel);
uint32_t get_green(Pixel *pixel);
uint32_t get_blue(Pixel *pixel);
uint32_t get_alpha(Pixel *pixel);

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