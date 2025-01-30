#ifndef _CTEST_DS_COMMON_H
#define _CTEST_DS_COMMON_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  void  *value;
  size_t bytes;
  void (*_delete)(void *);
} var_t;

int create_var_t(void *value, size_t bytes, void (*delete_value)(void *), var_t *var);
int delete_var_t(var_t *var);

#endif // _CTEST_DS_COMMON_H
