#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "array.h"

void _init_array(SizedArray *array, size_t element_size, size_t capacity)
{
    array->data = malloc(element_size * capacity);
    array->element_size = element_size;
    array->capacity = capacity;
}

SizedArray *new_array(size_t element_size, size_t capacity)
{
    SizedArray *array = malloc(sizeof(SizedArray));
    _init_array(array, element_size, capacity);
    return array;
}

void free_array(SizedArray *array)
{
    free(array->data);
    array->data = NULL;
    array->element_size = 0;
    array->capacity = 0;
}

void resize_array(SizedArray *array, size_t new_capacity)
{
    array->data = realloc(array->data, array->element_size * new_capacity);
    array->capacity = new_capacity;
}

void set_item(SizedArray *array, size_t index, void *element)
{
    if (index >= array->capacity)
    {
        fprintf(stderr, "index out of range\n");
        exit(1);
    }

    void *dest = (char *)array->data + array->element_size * index;
    memcpy(dest, element, array->element_size);
}

void *get_item(SizedArray *array, size_t index)
{
    if (index >= array->capacity)
    {
        fprintf(stderr, "index out of range\n");
        exit(1);
    }

    return (char *)array->data + array->element_size * index;
}

int *get_int_item(SizedArray *array, size_t index)
{
    return (int *)get_item(array, index);
}