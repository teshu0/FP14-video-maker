// 事前にサイズを定められる配列型の実装定義

#ifndef ARRAY_H // 複数回読み込みでのエラー防止らしい
#define ARRAY_H

#include <stdlib.h>

// dynamic array type definition

/// @brief 事前にサイズを定められる配列型
typedef struct
{
    void *data;
    size_t element_size; // それぞれの要素のサイズ
    size_t capacity;     // 保存可能な要素数
} SizedArray;

/// @brief 作成した配列を初期化する
/// @param array 配列
/// @param element_size 要素のサイズ
/// @param capacity 配列の初期容量
void _init_array(SizedArray *array, size_t element_size, size_t capacity);

SizedArray *new_array(size_t element_size, size_t capacity);

/// @brief 配列を解放する
/// @param array 配列
void free_array(SizedArray *array);

/// @brief 配列のサイズを変更する
/// @param array 配列
/// @param new_capacity 新しい容量
void resize_array(SizedArray *array, size_t new_capacity);

/// @brief 要素をセットする
/// @param array 配列
/// @param index セットするインデックス
/// @param element セットする要素
void set_item(SizedArray *array, size_t index, void *element);

/// @brief 要素を取得する(型キャストなし)
/// @param array
/// @param index
/// @return
void *get_item(SizedArray *array, size_t index);

/// @brief 要素を int 型で取得する
/// @param array
/// @param index
/// @return
int *get_int_item(SizedArray *array, size_t index);

#endif // ARRAY_H