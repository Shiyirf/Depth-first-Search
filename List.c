/*********************************************************************************
 * Shiyi Liu
 * 2022 Spring CSE101 PA3
 * CruzID: sliu223
 * List.c
 * The program of the List ADT
 *********************************************************************************/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// constructor of NodeObj
Node newNode(int x) {
  Node node = malloc(sizeof(NodeObj));
  node->data = x;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

// destructor of NodeObj
void freeNode(Node *pN) {
  if (pN == NULL || *pN == NULL) {
    fprintf(stderr, "Error in freeNode()! The node does not exist!\n");
    exit(EXIT_FAILURE);
  }

  free(*pN);
  *pN = NULL;
}

// Creates and returns a new empty List
List newList(void) {
  List list = malloc(sizeof(ListObj));
  list->front = NULL;
  list->back = NULL;
  list->cursor = NULL;
  list->length = 0;
  list->index = -1;
  return list;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List *pL) {
  if (pL == NULL || *pL == NULL) {
    fprintf(stderr, "Error in freeList()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }

  while ((*pL)->length > 0)
    deleteFront(*pL);

  free(*pL);
  *pL = NULL;
}

// Returns the number of elements in L.
int length(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in length()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  return L->length;
}

// Returns index of cursor element if defined, -1 otherwise
int index(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in index()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  return L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in front()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    fprintf(stderr, "Error in front()! The list is empty!\n");
    exit(EXIT_FAILURE);
  }
  return L->front->data;
}

// Returns back element of L. Pre: length()>0
int back(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in back()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    fprintf(stderr, "Error in back()! The list is empty!\n");
    exit(EXIT_FAILURE);
  }
  return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in get()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    fprintf(stderr, "Error in get()! The list is empty!\n");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

// Returns true iff Lists A and B are in same state, and returns false otherwise
bool equals(List A, List B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "Error in equals()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }

  if (A->length != B->length)
    return false;

  Node a = A->front;
  Node b = B->front;
  for (int i = 0; i < A->length; i++) {
    if (a->data != b->data)
      return false;

    a = a->next;
    b = b->next;
  }

  return true;
}

// Resets L to its original empty state
void clear(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in clear()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }

  while (L->length > 0) {
    deleteFront(L);
  }
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "Error in set()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {
    fprintf(stderr, "Error in set()! The list is empty!\n");
    exit(EXIT_FAILURE);
  }
  L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does
// nothing.
void moveFront(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in moveFront()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->length != 0) {
    L->cursor = L->front;
    L->index = 0;
  }
}

// If L is non-empty, sets cursor under the back element, otherwise does
// nothing.
void moveBack(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in moveBack()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->length != 0) {
    L->cursor = L->back;
    L->index = L->length - 1;
  }
}

// If cursor is defined and not at front, move cursor one step toward the front
// of L; if cursor is defined and at front, cursor becomes undefined; if cursor
// is undefined, do nothing
void movePrev(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in movePrev()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->index >= 1) {
    L->cursor = L->cursor->prev;
    L->index--;
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

// If cursor is defined and not at back, move cursor one step toward the back of
// L; if cursor is defined and at back, cursor becomes undefined; if cursor is
// undefined, do nothing
void moveNext(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in moveNext()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->index != -1) {
    if (L->index + 1 < L->length) {
      L->cursor = L->cursor->next;
      L->index += 1;
    } else {
      L->cursor = NULL;
      L->index = -1;
    }
  }
}

// Insert new element into L. If L is non-empty, insertion takes place before
// front element.
void prepend(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "Error in prepend()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  Node node = newNode(x);
  if (L->length == 0) {
    L->front = node;
    L->back = node;
  } else if (L->length > 0) {
    L->front->prev = node;
    node->next = L->front;
    L->front = node;
  }
  L->length++;
  if (L->index != -1)
    L->index++;
}

// Insert new element into L. If L is non-empty, insertion takes place after
// back element.
void append(List L, int data) {
  if (L == NULL) {
    fprintf(stderr, "Error in append()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  Node node = newNode(data);
  if (L->length == 0) {
    L->front = node;
    L->back = node;
  } else if (L->length > 0) {
    L->back->next = node;
    node->prev = L->back;
    L->back = node;
  }
  L->length++;
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "Error in insertBefore()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  Node node = newNode(x);
  if (L->cursor->prev != NULL) {
    L->cursor->prev->next = node;
    node->prev = L->cursor->prev;
  }
  L->cursor->prev = node;
  node->next = L->cursor;
  if (L->index == 0)
    L->front = node;

  L->length++;
  L->index++;
}

// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "Error in insertAfter()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  Node node = newNode(x);
  if (L->cursor->next != NULL) {
    L->cursor->next->prev = node;
    node->next = L->cursor->next;
  }
  L->cursor->next = node;
  node->prev = L->cursor;
  if (L->index == L->length - 1)
    L->back = node;

  L->length++;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in deleteFront()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    fprintf(stderr, "Error in deleteFront()! The list is empty!\n");
    exit(EXIT_FAILURE);
  }
  Node node = L->front;
  L->front = node->next;
  node->next = NULL;
  freeNode(&node);

  if (L->length > 1)
    L->front->prev = NULL;
  L->length--;

  if (L->index == 0) {
    L->cursor = NULL;
    L->index = -1;
  }
  if (L->index != -1)
    L->index--;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in deleteBack()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    fprintf(stderr, "Error in deleteBack()! The list is empty!\n");
    exit(EXIT_FAILURE);
  }
  Node node = L->back;
  L->back = node->prev;
  node->prev = NULL;
  freeNode(&node);

  if (L->index == L->length - 1) {
    L->cursor = NULL;
    L->index = -1;
  }
  if (L->length > 1)
    L->back->next = NULL;
  L->length--;
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete (List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in delete()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    fprintf(stderr, "Error in delete()! The list is empty!\n");
    exit(EXIT_FAILURE);
  }
  Node node = L->cursor;
  if (L->index == 0) {
    L->front = node->next;
    node->next = NULL;
    L->front->prev = NULL;
  } else if (L->index == L->length - 1) {
    L->back = node->prev;
    node->prev = NULL;
    L->back->next = NULL;
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = NULL;
  }
  L->cursor = NULL;
  L->index = -1;
  freeNode(&node);
  L->length--;
}

// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE *out, List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in printList()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    fprintf(out, "\n");
    return;
  }
  Node node = L->front;
  while (node != NULL) {
    fprintf(out, "%d ", node->data);
    node = node->next;
  }
  fprintf(out, "\n");
}

// Returns a new List representing the same integer sequence as L. The cursor in
// the new list is undefined, regardless of the state of the cursor in L. The
// state of L is unchanged.
List copyList(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in copyList()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  List new = newList();
  Node node = L->front;
  while (node != NULL) {
    append(new, node->data);
    node = node->next;
  }
  return new;
}

// Gives the value at a given position in the array
int getValue(List L, int pos) {
  if (L == NULL) {
    fprintf(stderr, "Error in getValue()! The list does not exist!\n");
    exit(EXIT_FAILURE);
  }
  if (L->length < pos) {
    fprintf(stderr, "Error in getValue()! Invalid pos!\n");
    return 0;
  }
  int p = 0;
  Node node = L->front;
  for (int i = 0; i < L->length; i++) {
    if (node == NULL)
      return 0;

    if (p == pos)
      return node->data;

    node = node->next;
    p++;
  }
  return -1;
}
