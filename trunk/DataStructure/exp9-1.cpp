#include <stdio.h>
#include <stdlib.h>


#define MAXV 100
#define INF 32767

typedef struct {
	int no;
	int info;
} VertexType;

typedef struct {
	int edges[MAXV][MAXV];
	int n, e;
	VertexType vexs[MAXV];
} MGraph;

typedef struct ANode {
	int adjvex;
	struct ANode *nextarc;
	int info;
} ArcNode;

typedef struct Vnode {
	int data;
	ArcNode *firstarc;
} VNode;

typedef VNode AdjList[MAXV];

typedef struct {
	AdjList adjlist;
	int n, e;
} ALGraph;

void MatToList(MGraph g, ALGraph *&G)
{
	int i, j, n = g.n;
	ArcNode *p;
	G = (ALGraph *)malloc(sizeof(ALGraph));
	for (i = 0; i < n; i++) 
		G->adjlist[i].firstarc = NULL;
	for (i = 0; i < n; i++)
		for (j = n - 1; j >= 0; j--)
			if (g.edges[i][j] != 0) {
				p = (ArcNode *)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->nextarc = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
	G->n = n;
	G->e = g.e;
}

void ListToMat(ALGraph *G, MGraph &g)
{
	int i, n = G->n;
	ArcNode *p;
	for (i = 0; i < n; i++) {
		p = G->adjlist[i].firstarc;
		while (p) {
			g.edges[i][p->adjvex] = 1;
			p = p->nextarc;
		}
	}
	g.n = n;
	g.e = G->e;
}

void DispMat(MGraph g)
{
	int i, j;
	for (i = 0; i < g.n; i++) {
		for (j = 0; j < g.n; j++)
			if (g.edges[i][j] == INF)
				printf ("INF");
			else
				printf("%5d", g.edges[i][j]);
		puts("");
	}
}

void DispAdj(ALGraph *G)
{
	int i;
	ArcNode *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		if (p) printf("%5d", i);
		while (p) {
			printf("%5d", p->adjvex);
			p = p->nextarc;
		}
		printf("\n");
	}
}


int main(int argc, char **argv)
{
	int i, j;
	MGraph g, g1;
	ALGraph *G;
	int A[MAXV][6] = {
		{ 0, 5, 0, 7, 0, 0},
		{ 0, 0, 4, 0, 0, 0},
		{ 8, 0, 0, 0, 0, 9},
		{ 0, 0, 5, 0, 0, 6},
		{ 0, 0, 0, 5, 0, 0},
		{ 3, 0, 0, 0, 1, 0}
	};

	g.n = 6;
	g.e = 10;

	for (i = 0; i < g.n; i++) 
		for (j = 0; j < g.n; j++)
			g.edges[i][j] = A[i][j];
	puts("");
	printf("1: \n");
	DispMat(g);
	G = (ALGraph *)malloc(sizeof(ALGraph));
	printf("2: \n");
	MatToList(g, G);
	DispAdj(G);
	printf("3:\n");
	ListToMat(G, g1);
	DispMat(g1);
	puts("");
	return 0;
}
