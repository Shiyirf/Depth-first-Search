/****************************************************************************************
 * Shiyi Liu
 * 2022 Spring CSE101 PA3
 * CruzID: sliu223
 * Graph.c
 * The program of the Graph ADT
 *****************************************************************************************/

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj {
  List *adj;
  int order;
  int size;
  int *color;
  int *parent;
  int *discover;
  int *finish;
} GraphObj;

Graph newGraph(int n) {
  Graph G = malloc(sizeof(GraphObj));
  G->adj = malloc((n + 1) * sizeof(List));
  for (int i = 1; i <= n; i++) {
    G->adj[i] = newList();
  }
  G->color = malloc((n + 1) * sizeof(int));
  G->parent = malloc((n + 1) * sizeof(int));
  G->discover = malloc((n + 1) * sizeof(int));
  G->finish = malloc((n + 1) * sizeof(int));
  G->size = 0;
  G->order = n;
  return G;
}

void freeGraph(Graph *pG) {
  if (pG == NULL || *pG == NULL) {
    fprintf(stderr, "Error in freeGraph()! The node does not exist!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= getOrder(*pG); i++) {
    freeList(&(*pG)->adj[i]);
  }
  free((*pG)->adj);
  free((*pG)->color);
  free((*pG)->parent);
  free((*pG)->discover);
  free((*pG)->finish);
  free(*pG);
  *pG = NULL;
}

int getOrder(Graph G) { 
  return G->order; 
}

int getSize(Graph G) { 
  return G->size; 
}

int getParent(Graph G, int u) {
  if (u < 1 || G->order < u) {
    fprintf(stderr, "Error in getParent()!");
    exit(EXIT_FAILURE);
  }
  return G->parent[u];
}

int getDiscover(Graph G, int u) {
  if (u < 1 || G->order < u) {
    fprintf(stderr, "Error in getDiscover()!");
    exit(EXIT_FAILURE);
  }
  return G->discover[u];
}

int getFinish(Graph G, int u) {
  if (u < 1 || G->order < u) {
    fprintf(stderr, "Error in getDiscover()!");
    exit(EXIT_FAILURE);
  }
  return G->finish[u];
}

void addEdge(Graph G, int u, int v) {
  if (u < 1 || G->order < u || v < 1 || G->order < v) {
    fprintf(stderr, "Error in addEdge()!");
    exit(EXIT_FAILURE);
  }
  addArc(G, u, v);
  addArc(G, v, u);
  G->size--;
}

void addArc(Graph G, int u, int v) {
  if (u < 1 || G->order < u || v < 1 || G->order < v) {
    fprintf(stderr, "Error in addArc()!");
    exit(EXIT_FAILURE);
  }
  if (length(G->adj[u]) == 0) {
    append(G->adj[u], v);
    G->size++;
  } else {
    int l = length(G->adj[u]);
    for (int i = 1; i <= l; i++) {
      int zeroIndex = 0;
      moveBack(G->adj[u]);
      for (int j = length(G->adj[u]) - 1; j >= 0; j--) {
        if (v == get(G->adj[u])) {
          return;
        }
        if (v < get(G->adj[u])) {
          if (j == 0)
            zeroIndex = 1;
          else
            movePrev(G->adj[u]);
        }
      }
      if (zeroIndex == 1) {
        insertBefore(G->adj[u], v);
        G->size++;
      }

      else {
        insertAfter(G->adj[u], v);
        G->size++;
      }
    }
  }
}

int Visit(Graph G, int x, int time, List S) {
  G->discover[x] = ++time;
  G->color[x] = GRAY;
  if (length(G->adj[x])) {
    for (moveFront(G->adj[x]); index(G->adj[x]) != -1; moveNext(G->adj[x])) {
      if (G->color[get(G->adj[x])] == WHITE) {
        G->parent[get(G->adj[x])] = x;
        time = Visit(G, get(G->adj[x]), time, S);
      }
    }
  }
  G->color[x] = BLACK;
  G->finish[x] = ++time;
  prepend(S, x);
  return time;
}

void DFS(Graph G, List S) {
  if (S == NULL) {
    fprintf(stderr, "Error in DFS()!");
    exit(EXIT_FAILURE);
  }
  List L = copyList(S);
  clear(S);
  for (int i = 0; i <= G->order; i++) {
    G->color[i] = WHITE;
    G->parent[i] = NIL;
  }
  int time = 0;
  for (moveFront(L); index(L) != -1; moveNext(L)) {
    if (G->color[get(L)] == WHITE) {
      time = Visit(G, get(L), time, S);
    }
  }
  clear(L);
  freeList(&L);
}

Graph transpose(Graph G) {
  Graph T = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    if (length(G->adj[i])) {
      moveFront(G->adj[i]);
      while (index(G->adj[i]) != -1) {
        addArc(T, get(G->adj[i]), i);
        moveNext(G->adj[i]);
      }
    }
  }
  return T;
}

Graph copyGraph(Graph G) {
  Graph C = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    if (length(G->adj[i])) {
      moveFront(G->adj[i]);
      while (index(G->adj[i]) != -1) {
        addArc(C, i, get(G->adj[i]));
        moveNext(G->adj[i]);
      }
    }
  }
  return C;
}

void printGraph(FILE *out, Graph G) {
  for (int i = 1; i <= getOrder(G); i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->adj[i]);
  }
}
