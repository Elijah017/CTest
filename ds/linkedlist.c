// vim:fdm=marker
#include "linkedlist.h"

int linkedlist_init(LinkedList *list) { /*{{{*/
  memset(list, 0, sizeof(*list));
  return 0;
}/*}}}*/

int linkedlist_append(var_t *node, LinkedList *list) { /*{{{*/
  ListNode *ln = malloc(sizeof(ListNode));

  if (ln == NULL) {
    perror("failed to allocated ListNode\n");
    return errno;
  }

  memcpy(&(ln->value), node, sizeof(var_t));
  ln->next = NULL;

  if (list->head == NULL) { list->head = ln; }
  else {
    ListNode *prev = list->head;
    while (prev->next != NULL) prev = prev->next;

    prev->next = ln;
  }

  list->length++;
  return 0;
} /*}}}*/

int linkedlist_pop_index(size_t index, var_t *node, LinkedList *list) { /*{{{*/
  if (index > list->length) { return -1; }

  ListNode *prev = NULL, *n = list->head;
  for (size_t i = 0; i < index; i++) {
    prev = n;
    n    = n->next;
  }

  if (node == NULL) { delete_var_t(&(n->value)); }
  else {
    if (create_var_t(n->value.value, n->value.bytes, n->value._delete, node) != 0) {
      perror("failed to create var_t when popping linkedlist index\n");
      return errno;
    }
  }

  if (prev == NULL) { list->head = n->next; }
  else { prev->next = n->next; }

  list->length--;
  free(n);
  return 0;
} /*}}}*/

void linkedlist_delete(LinkedList *list) {/*{{{*/
  if (list->length == 0) { return; }

  ListNode *node = list->head;
  for (size_t i = 0; i < list->length; i++) {
    delete_var_t(&(node->value));
    free(node);
  }

  list->head = NULL;
} /*}}}*/
