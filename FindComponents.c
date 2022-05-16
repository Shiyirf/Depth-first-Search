/****************************************************************************************
 * Shiyi Liu
 * 2022 Spring CSE101 PA3
 * CruzID: sliu223
 * FindCoponents.c
 * The program of the FindComponents
 *****************************************************************************************/

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *in, *out;
  int n;

  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if (in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if (out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  fscanf(in, "%d", &n);
  Graph G = newGraph(n);

  int u, v;
  while (fscanf(in, "%d %d\n", &u, &v) && u != 0)
    addArc(G, u, v);

  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\n");
  List S = newList();
  for (int i = 1; i <= n; i++)
    append(S, i);

  DFS(G, S);

  Graph T = transpose(G);
  DFS(T, S);
  int s = 0;

  for (moveFront(S); index(S) != -1; moveNext(S)) {
    if (getParent(T, get(S)) == NIL)
      s++;
  }

  fprintf(out, "G contains %d strongly connected components:\n", s);

  List L = newList();

  for (int i = 1; i <= s; i++) {
    fprintf(out, "Component %d: ", i);
    while (getParent(T, back(S)) != NIL) {
      prepend(L, back(S));
      deleteBack(S);
    }
    prepend(L, back(S));
    printList(out, L);
    clear(L);
    deleteBack(S);
  }

  freeList(&L);
  freeList(&S);
  freeGraph(&G);
  freeGraph(&T);
  fclose(in);
  fclose(out);
  return 0;
}
