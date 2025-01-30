// vim: set fdm=marker
#ifndef _CTEST_SHARED_LINKEDLIST_H
#define _CTEST_SHARED_LINKEDLIST_H

#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "../common.h"

typedef struct _listnode {
  var_t             value;
  struct _listnode *next;
} ListNode;

typedef struct {
  size_t    length;
  ListNode *head;
} LinkedList;

/**
 * initialises an empty `LinkedList` struct
 *
 * @param list pointer to the list that will be initialised
 *
 * @return `0` | `errno`
 *
 * @exception `ENOMEM`
 */
int linkedlist_init(LinkedList *list);

/**
 * append a node to the end of the list
 *
 * @param node pointer to the an initialised variable type
 * @param list pointer to the list to append to
 *
 * @return `0` | `errno`
 *
 * @exception `ENOMEM`
 */
int linkedlist_append(var_t *node, LinkedList *list);

/**
 * Pop the value at a given index. If the index is out of range the function
 * will return `-1`. It becomes the users responsiblity to manage the memory of
 * the returned `var_t`
 *
 * @param index index to pop from
 * @param node variable type that will be initialsed with the value of the node
 * at the supplied index. If node is NULL popped value will be deleted.
 * @param list LinkedList to pop from
 *
 * @return `0` | `-1` | `errno`
 */
int linkedlist_pop_index(size_t index, var_t *node, LinkedList *list);

/**
 * delete the given LinkedList
 */
void linkedlist_delete(LinkedList *list);

#endif // _CTEST_SHARED_LINKEDLIST_H
