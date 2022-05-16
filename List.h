/*********************************************************************************
 * Shiyi Liu
 * 2022 Spring CSE101 PA3
 * CruzID: sliu223
 * List.h
 * The header of the List ADT
 *********************************************************************************/
#pragma once

#include <stdbool.h>
#include <stdio.h>

// the node in the ListADT
typedef struct NodeObj {
  int data;
  struct NodeObj *prev;
  struct NodeObj *next;
} NodeObj;

typedef struct NodeObj *Node;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

typedef struct ListObj *List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List *pL);

// Access functions -----------------------------------------------------------
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void movePrev(List L);
void moveNext(List L);
void moveBack(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete (List L);

// Other operations -----------------------------------------------------------
void printList(FILE *out, List L);
List copyList(List L);

// Help operations -----------------------------------------------------------
int getValue(List L, int pos);
