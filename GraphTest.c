/****************************************************************************************
 * Shiyi Liu
 * 2022 Spring CSE101 PA3
 * CruzID: sliu223
 * GraphTest.c
 * The test program of the Graph ADT
 *****************************************************************************************/

//-----------------------------------------------------------------------------
// GraphTest.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i, n = 8;
  List S = newList();
  Graph G = newGraph(n);
  Graph T = NULL, C = NULL;

  for (i = 1; i <= n; i++)
    append(S, i);

  addArc(G, 1, 2);
  addArc(G, 1, 3);
  addArc(G, 2, 5);
  addArc(G, 2, 6);
  addArc(G, 3, 1);
  addArc(G, 3, 4);
  addArc(G, 3, 6);
  addArc(G, 3, 7);
  addArc(G, 3, 8);
  addArc(G, 6, 4);
  addArc(G, 6, 7);
  addArc(G, 8, 4);
  addArc(G, 8, 7);
  printGraph(stdout, G);

  DFS(G, S);
  fprintf(stdout, "\n");
  fprintf(stdout, "x:  d  f  p\n");
  for (i = 1; i <= n; i++) {
    fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i),
            getParent(G, i));
  }
  fprintf(stdout, "\n");
  printList(stdout, S);
  fprintf(stdout, "\n");

  T = transpose(G);
  C = copyGraph(G);
  fprintf(stdout, "\n");
  printGraph(stdout, C);
  fprintf(stdout, "\n");
  printGraph(stdout, T);
  fprintf(stdout, "\n");

  DFS(T, S);
  fprintf(stdout, "\n");
  fprintf(stdout, "x:  d  f  p\n");
  for (i = 1; i <= n; i++) {
    fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i),
            getParent(T, i));
  }
  fprintf(stdout, "\n");
  printList(stdout, S);
  fprintf(stdout, "\n");

  freeList(&S);
  freeGraph(&G);
  freeGraph(&T);
  freeGraph(&C);
  return (0);
}

/*
Output of this program:
1: 2 3
2: 5 6
3: 1 4 6 7 8
4:
5:
6: 4 7
7:
8: 4 7

x:  d  f  p
1:  1 16  0
2:  2 11  1
3: 12 15  1
4:  6  7  6
5:  3  4  2
6:  5 10  2
7:  8  9  6
8: 13 14  3

1 3 8 2 6 7 4 5


1: 2 3
2: 5 6
3: 1 4 6 7 8
4:
5:
6: 4 7
7:
8: 4 7

1: 3
2: 1
3: 1
4: 3 6 8
5: 2
6: 2 3
7: 3 6 8
8: 3


x:  d  f  p
1:  1  4  0
2:  7  8  0
3:  2  3  1
4: 13 14  0
5: 15 16  0
6:  9 10  0
7: 11 12  0
8:  5  6  0

5 4 7 6 2 8 1 3
*/
