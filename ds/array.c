// vim: fdm=marker
#include "array.h"

int array_init(size_t  size, /*{{{*/
               size_t  capacity,
               void ( *delete_item )(void *),
               char *(*item2str)(void *),
               Array  *array) {
  capacity     = capacity < ARRAY_MIN ? ARRAY_MIN : capacity;
  array->items = malloc(size * capacity);

  if (array->items == NULL) {
    perror("failed to allocate space for an array\n");
    return errno;
  }

  array->size      = size;
  array->capacity  = capacity;
  array->length    = 0;
  array->_delete   = delete_item;
  array->_item_str = item2str;

  return 0;
} /*}}}*/

int array_append(void *item, Array *array) {/*{{{*/
  if ((array->length == array->capacity) && (_array_grow(ARRAY_SCALE, array) != 0)) {
    perror("failed to grow array during append\n");
    return errno;
  }

  void *insert_pointer = array_get(array->length, array);
  memcpy(insert_pointer, item, array->size);
  array->length++;

  return 0;
} /*}}}*/

int array_insert(void *item, size_t index, Array *array) {/*{{{*/
  if ((index > array->length) || (index < 0)) { return 1; }

  if ((array->length == array->capacity) && (_array_grow(ARRAY_SCALE, array) != 0)) {
    perror("failed to grow array during append\n");
    return errno;
  }

  _array_shift_right(index, array);

  void *insert_pointer = array_get(index, array);
  memcpy(insert_pointer, item, array->size);
  array->length++;

  return 0;
} /*}}}*/

int array_remove_index(size_t index, Array *array) { /*{{{*/
  if ((array->length == 0) || (index >= array->length)) { return 1; }

  if (index == array->length - 1) {
    array_pop_right(NULL, array);
    return 0;
  }

  void *delete_pointer = array_get(index, array);

  if (array->_delete != NULL) { array->_delete(delete_pointer); }

  _array_shift_left(index + 1, array);
  array->length--;
  return 0;
} /*}}}*/

int array_pop_right(void *item, Array *array) {/*{{{*/
  if (array->length == 0) { return 1; }

  void *extract_pointer = array_get(array->length - 1, array);

  if (item != NULL) { memcpy(item, extract_pointer, array->size); }
  else if (array->_delete != NULL) { array->_delete(extract_pointer); }
  else { memset(extract_pointer, 0, array->size); }

  array->length--;
  return 0;
} /*}}}*/

int array_pop_left(void *item, Array *array) {/*{{{*/
  if (array->length == 0) { return 1; }

  void *extract_pointer = array->items;

  if (item != NULL) { memcpy(item, extract_pointer, array->size); }
  else if (array->_delete != NULL) { array->_delete(extract_pointer); }

  _array_shift_left(1, array);
  array->length--;
  return 0;
} /*}}}*/

int array_delete(Array *array) {/*{{{*/
  if (array->_delete == NULL) {
    free(array->items);
    array->items = NULL;
    return 0;
  }

  for (size_t i = 0; i < array->length; i++) array->_delete(array_get(i, array));

  free(array->items);
  array->items = NULL;
  return 0;
} /*}}}*/

void* array_get(size_t index, Array *array) {/*{{{*/
  if (index > array->length) { return NULL; }
  return array->items + (index * array->size);
} /*}}}*/

void array_print(Array *array) {/*{{{*/
  printf("[ ");
  for (size_t i = 0; i < array->length; i++) {
    char *str;

    if (array->_item_str == NULL) {
      str = malloc(sizeof(*str) * 19); // 19 = 8 bytes (hex) + 0x + \0
      snprintf(str, 19, "%p", array_get(i, array));
    } else {
      str = array->_item_str(array_get(i, array));
    }

    if (i == array->length - 1) { printf("%s ", str); }
    else { printf("%s, ", str); }

    free(str);
    str = NULL;
  }
  printf("]\n");
} /*}}}*/

int _array_grow(float scale, Array *array) {/*{{{*/
  if (scale <= 1) { return 1; }

  size_t capacity = array->capacity * scale;
  void  *temp     = realloc(array->items, array->size * capacity);

  if (temp == NULL) {
    perror("failed to realloc space for array grow\n");
    return errno;
  }

  array->capacity = capacity;
  array->items    = temp;
  return 0;
} /*}}}*/

int _array_shrink(float scale, Array *array) {/*{{{*/
  if (scale >= 1) { return 1; }

  size_t capacity = array->capacity * scale;

  if (capacity < array->length) { return 1; }

  void *temp = realloc(array->items, capacity * array->size);

  if (temp == NULL) {
    perror("failed to shrink array size\n");
    return errno;
  }

  array->capacity = capacity;
  array->items    = temp;
  return 0;
} /*}}}*/

int _array_shift_right(size_t index, Array *array) { /*{{{*/
  if ((array->length == array->capacity) && (_array_grow(ARRAY_SCALE, array) != 0)) {
    perror("failed to grow array for shift right\n");
    return errno;
  }

  void *src  = array_get(index, array);
  void *dest = src + array->size;
  memmove(dest, src, array->size * (array->length - index));

  return 0;
} /*}}}*/

int _array_shift_left(size_t index, Array *array) { /*{{{*/
  if (index < 1) { return 1; }

  void *src  = array_get(index, array);
  void *dest = src - array->size;
  memmove(dest, src, array->size * (array->length - index));
} /*}}}*/
