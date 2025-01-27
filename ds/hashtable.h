#ifndef _CTEST_SHARED_HASHTABLE_H
#define _CTEST_SHARED_HASHTABLE_H

#include <unistd.h>

#define GROW 0.6
#define SHRINK 0.1
#define HT_MIN_SIZE 50

enum hash { FNV_1A_32, FNV_1A_64 };

typedef struct {
  void  *chunk;
  size_t size;
} var_t;

typedef struct _entry {
  var_t          key;
  var_t          value;
  struct _entry *next;
} entry;

typedef struct {
  entry *entries;
  size_t length;
  size_t size;
  enum hash _hash;
} hashtable;

int hashtable_init(size_t *size, enum hash *hash, hashtable *table);
int hashtable_delete(hashtable *table);
int hashtable_insert(var_t *key, var_t *value, hashtable *table);
int hashtable_remove_entry(entry *entry, hashtable *table);
int hashtable_remove_key(var_t *key, hashtable *table);

#endif // _CTEST_SHARED_HASHTABLE_H
