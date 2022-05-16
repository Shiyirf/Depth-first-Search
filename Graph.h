/*********************************************************************************
 * Shiyi Liu
 * 2022 Spring CSE101 PA3
 * CruzID: sliu223
 * Graph.h
 * The header of the Graph ADT
 *********************************************************************************/

#pragma once

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

#define INF -1
#define NIL 0
#define UNDEF 0

typedef struct GraphObj *Graph;
// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph *pG);
// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
// Manipulation procedures
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List S);
// Other Functions
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);
