// vim: fdm=marker
#ifndef _CTEST_SHARED_ARRAY_H
#define _CTEST_SHARED_ARRAY_H

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define ARRAY_SCALE 1.2f
#define ARRAY_MIN   10

typedef struct {
  void  *items;
  size_t size;
  size_t length;
  size_t capacity;
  void (*_delete)(void *);
  char *(*_item_str)(void *);
} Array;

int array_init(size_t size, size_t  capacity, void (*delete_item)(void *),
               char *(*item2str)(void *), Array  *array);
int array_append(void *item, Array *array);
int array_insert(void *item, size_t index, Array *array);
int array_remove_index(size_t index, Array *array);
int array_pop_right(void *item, Array *array);
int array_pop_left(void *item, Array *array);
int array_delete(Array *array);
void* array_get(size_t index, Array *array);
void array_print(Array *array);

int _array_grow(float scale, Array *array);
int _array_shift_right(size_t index, Array *array);
int _array_shift_left(size_t index, Array *array);

#endif // _CTEST_SHARED_ARRAY_H
