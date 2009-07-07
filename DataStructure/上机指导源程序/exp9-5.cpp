/*文件名:exp9-5.cpp*/
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList(MGraph,ALGraph *&);	/*以下外部函数在algo9-1.cpp中*/
extern void DispAdj(ALGraph *);
int visited[MAXV];							/*全局数组*/
void DFS(ALGraph *G,int v) 
{
	ArcNode *p;
	visited[v]=1;                   		/*置已访问标记*/
	p=G->adjlist[v].firstarc;      			/*p指向顶点v的第一条弧的弧头结点*/
	while (p!=NULL) 
	{	
		if (visited[p->adjvex]==0)			/*若p->adjvex顶点未访问,递归访问它*/
		{
			printf("<%d,%d> ",v,p->adjvex);	/*输出生成树的一条边*/
			DFS(G,p->adjvex);    
		}
		p=p->nextarc;              			/*p指向顶点v的下一条弧的弧头结点*/
	}
}
void BFS(ALGraph *G,int v)  
{
	ArcNode *p;
	int queue[MAXV],front=0,rear=0;			/*定义循环队列并初始化*/
	int visited[MAXV];            			/*定义存放结点的访问标志的数组*/
	int w,i;
	for (i=0;i<G->n;i++) 
		visited[i]=0;						/*访问标志数组初始化*/
	visited[v]=1;              				/*置已访问标记*/
	rear=(rear+1)%MAXV;
	queue[rear]=v;             				/*v进队*/
	while (front!=rear)       				/*若队列不空时循环*/
	{	
		front=(front+1)%MAXV;
		w=queue[front];       				/*出队并赋给w*/
		p=G->adjlist[w].firstarc; 			/*找与顶点w邻接的第一个顶点*/
		while (p!=NULL) 
		{	
			if (visited[p->adjvex]==0) 		/*若当前邻接顶点未被访问*/
			{	
				printf("<%d,%d> ",w,p->adjvex);	/*输出生成树的一条边*/
				visited[p->adjvex]=1;		/*置该顶点已被访问的标志*/
				rear=(rear+1)%MAXV;			/*该顶点进队*/
				queue[rear]=p->adjvex; 		
           	}
           	p=p->nextarc;              		/*找下一个邻接顶点*/
		}
	}
	printf("\n");
}
void main()
{ 
	int i,j;
	MGraph g;
	ALGraph *G;
	int A[MAXV][11];
	g.vexnum=11;g.arcnum=13;
	for (i=0;i<g.vexnum;i++)
		for (j=0;j<g.vexnum;j++)
			A[i][j]=0;
	A[0][3]=1;A[0][2]=1;A[0][1]=1;
	A[1][5]=1;A[1][4]=1;
	A[2][6]=1;A[2][5]=1;A[2][3]=1;
	A[3][7]=1;
	A[6][9]=1;A[6][8]=1;A[6][7]=1;
	A[7][10]=1;
	for (i=0;i<g.vexnum;i++)
		for (j=0;j<g.vexnum;j++)
			A[j][i]=A[i][j];
	for (i=0;i<g.vexnum;i++)		/*建立图图9.12的邻接矩阵*/
		for (j=0;j<g.vexnum;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g,G);
	printf("\n");
	printf("图G的邻接表:\n");
	DispAdj(G);
	printf("\n");
	for (i=0;i<g.vexnum;i++) 
		visited[i]=0;
	printf("深度优先生成树:");
	DFS(G,3);printf("\n");
	for (i=0;i<g.vexnum;i++) 
		visited[i]=0;
	printf("广度优先生成树:");
	BFS(G,3);printf("\n");
}
