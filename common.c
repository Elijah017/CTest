#include "common.h"

int create_var_t(void *value, size_t bytes, void (*delete_value)(void *), var_t *var) {
  var->value = malloc(bytes);

  if (var->value == NULL) {
    perror("failed to allocate variable type\n");
    return errno;
  }

  memcpy(var->value, value, bytes);
  var->bytes   = bytes;
  var->_delete = delete_value;
  return 0;
}

int delete_var_t(var_t *var) {
  if (var->_delete != NULL) { var->_delete(var->value); }
  free(var->value);
  var->value = NULL;
  return 0;
}
