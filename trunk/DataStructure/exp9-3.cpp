#include <stdio.h>
#include <malloc.h>

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

int visited[MAXV];						

void PathAll1(ALGraph *G, int u, int v, int path[], int i)
{
	ArcNode *p;
	int j, n;
	visited[u] = 1;
	p = G->adjlist[u].firstarc;  			
	while (p != NULL)
	{
		n = p->adjvex;				
		if (n == v)
		{
			path[i+1] = v;
			for (j = 0; j <= i+1; j++)
				printf("%3d", path[j]);
			printf("\n");
		}
		else if (visited[n] == 0 ) 
		{
			path[i+1] = n;
			PathAll1( G, n, v, path, i+1);
		}
		p = p->nextarc;			
	}
	visited[u] = 0;
}
void PathAll2(ALGraph *G, int u, int v, int l, int path[], int d)
{
	int m, i;
	ArcNode *p;
	visited[u] = 1;
	d++;							
	path[d] = u;					
	if (u == v && d == l)		
	{
		for (i = 0; i <= d; i++)
			printf("%3d", path[i]);
		printf("\n");
	}
	p = G->adjlist[u].firstarc;  		
	while (p != NULL)
	{
		m = p->adjvex;			
		if (visited[m] == 0)	
			PathAll2( G, m, v, l, path, d);
		p = p->nextarc;	
	}
	visited[u] = 0;	
	d--;		
}


int ShortPath(ALGraph *G, int u, int v, int path[])
{
	struct 
	{
		int vno;						
		int level;					
		int parent;				
	} qu[MAXV];				
	int front = -1, rear = -1, k, lev, i, j;
	ArcNode *p;
	visited[u] = 1;
	rear++;				
	qu[rear].vno = u;
	qu[rear].level = 0;
	qu[rear].parent = -1;
	while (front < rear)
	{
		front++;
		k = qu[front].vno;
		lev = qu[front].level;
		if (k == v) 
		{
			i = 0;
			j = front;
			while (j != -1)
			{
				path[lev-i] = qu[j].vno;	
				j = qu[j].parent;
				i++;
			}
			return lev;				
		}
		p = G->adjlist[k].firstarc;
		while (p != NULL)         
		{
			if (visited[p->adjvex] == 0)  
			{
				visited[p->adjvex] = 1;
				rear++;
				qu[rear].vno = p->adjvex;
				qu[rear].level = lev+1;
				qu[rear].parent = front;
			}
			p = p->nextarc;			
		}
	}
	return 0;     
}

int main(int argc, char **argv)
{ 
	int i,j;
	int u = 5, v = 2, d = 3;
	int path[MAXV];
	MGraph g;
	ALGraph *G;
	int A[MAXV][6] = {
		{0,1,0,1,0,0},
		{0,0,1,0,0,0},
		{1,0,0,0,0,1},
		{0,0,1,0,0,1},
		{0,0,0,1,0,0},
		{1,1,0,1,1,0}};
	g.n = 6; 
	g.e = 10;

	for (i = 0; i < g.n; i++)		
		for (j = 0; j < g.n; j++)
			g.edges[i][j] = A[i][j];

	G = (ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g, G);				
	printf("1:\n");
	DispAdj(G);
	printf("\n");

	for (i = 0; i < g.n; i++) 
		visited[i]=0;
	printf("2:\n");
	path[0] = u;
	visited[u] = 1;
	PathAll1( G, u, v, path, 0);
	printf("\n");

	printf("3:\n");
	PathAll2( G, u, v, d, path, -1);
	printf("\n");

	for (i = 0; i < g.n; i++) 
		visited[i] = 0;
	printf("4:\n");
	for (i = 0; i < g.n; i++) 
		visited[i]=0;
	j = ShortPath( G, u, v, path);
	for (i = 0; i <= j; i++)
		printf("%3d", path[i]);
	printf("\n\n");
}
