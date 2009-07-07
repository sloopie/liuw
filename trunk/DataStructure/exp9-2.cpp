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

int visited[MAXV];

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
				printf("%3d", g.edges[i][j]);
		puts("");
	}
}

void DispAdj(ALGraph *G)
{
	int i;
	ArcNode *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		if (p) printf("%3d", i);
		while (p) {
			printf("%3d", p->adjvex);
			p = p->nextarc;
		}
		printf("\n");
	}
}


void DFS(ALGraph *G, int v)
{
	ArcNode *p;
	visited[v] = 1;
	printf("%3d", v);
	p = G->adjlist[v].firstarc;
	while (p) {
		if (visited[p->adjvex] == 0)
			DFS(G, p->adjvex);
		p = p->nextarc;
	}
}

void DFS1(ALGraph *G, int v)
{
	int i, visited[MAXV], St[MAXV], top = -1;
	ArcNode *p;
	for (i = 0; i < G->n; i++)
		visited[i] = 0;
	printf("%3d", v);
	top++;
	St[top] = v;
	visited[v] = 1;
	while (top >= -1) {
		v = St[top];
		top--;
		p = G->adjlist[v].firstarc;
		while (p && visited[p->adjvex] == 1)
			p = p->nextarc;
		if (!p)
			top--;
		else {
			v = p->adjvex;
			printf("%3d", v);
			visited[v] = 1;
			top++;
			St[top] = v;
		}
	}
	puts("");
}

int BFS(ALGraph *G, int v)
{
	ArcNode *p;
	int queue[MAXV], front = 0, rear = 0;
	int visited[MAXV];
	int w, i;
	for (i = 0; i < G->n; i++) visited[i] = 0;
	printf("%3d", v);
	visited[v] = 1;
	rear = (rear + 1) % MAXV;
	queue[rear] = v;
	while (front != rear) {
		front = (front + 1) % MAXV;
		w = queue[front];
		p = G->adjlist[w].firstarc;
		while (p) {
			if (visited[p->adjvex] == 0) {
				printf("%3d", p->adjvex);
				visited[p->adjvex] = 1;
				rear = (rear + 1) % MAXV;
				queue[rear] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
	puts("");
}

int main(int argc, char **argv)
{
	int i,j;
	MGraph g;
	ALGraph *G;
	int A[MAXV][6] = {
		{ 0, 5, 0, 7, 0, 0},
		{ 0, 0, 4, 0, 0, 0},
		{ 8, 0, 0, 0, 0, 9},
		{ 0, 0, 5, 0, 0, 6},
		{ 0, 0, 0, 5, 0, 0},
		{ 3, 0, 0, 0, 1, 0}};
	g.n = 6;
	g.e = 10;
	for (i = 0; i < g.n; i++)		
		for (j = 0;j < g.n; j++)
			g.edges[i][j] = A[i][j];
	G = (ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g,G);			
	printf("1:\n");
	DispAdj(G);
	printf("2:\n");
	DFS(G,0);
	printf("\n");
	printf("3:\n");
	DFS1(G,0);
	printf("4:\n");
	BFS(G,0);
	printf("\n");
	return 0;
}
