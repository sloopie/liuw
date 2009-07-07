/*文件名:exp9-4.cpp*/
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList(MGraph,ALGraph *&);	/*以下外部函数在algo9-1.cpp中*/
extern void DispAdj(ALGraph *);
int visited[MAXV],path[MAXV];				/*全局数组*/
int V1[MAXV],V2[MAXV],n,m; 
int Cond(int path[],int d)	/*判断条件*/
{
	int flag1=0,f1,flag2=0,f2,i,j;
	for (i=0;i<n;i++)		/*判断路径中是否有必经点*/
	{
		f1=1;
		for (j=0;j<=d;j++)
			if (path[j]==V1[i])
			{
				f1=0;break;
			}
		flag1+=f1;
	}

	for (i=0;i<m;i++)		/*判断路径中是否有必避点*/
	{
		f2=0;
		for (j=0;j<=d;j++)
			if (path[j]==V2[i])
			{
				f2=1;break;
			}
		flag2+=f2;
	}
	if (flag1==0 && flag2==0)
		return 1;
	else
		return 0;
}
void TravPath(ALGraph *G,int vi,int vj,int d)
{
	int v,i;
	ArcNode *p;
	visited[vi]=1;
	d++;
	path[d]=vi;
	if (vi==vj && Cond(path,d)==1)
	{
		for (i=0;i<=d;i++)
			printf("%3d",path[i]);
		printf("\n");
	}
    p=G->adjlist[vi].firstarc;      /*找vi的第一个邻接顶点*/
	while (p!=NULL)
	{
		v=p->adjvex;                /*v为vi的邻接顶点*/
		if (visited[v]==0)          /*若该顶点未标记访问,则递归访问之*/
			TravPath(G,v,vj,d);
		p=p->nextarc;               /*找vi的下一个邻接顶点*/
	}
	visited[vi]=0;                  /*取消访问标记,以使该顶点可重新使用*/
	d--;
}
void main()
{ 
	int i,j,u,v;
	MGraph g;
	ALGraph *G;
	int A[MAXV][15];
	g.vexnum=15;g.arcnum=20;
	for (i=0;i<g.vexnum;i++)
		for (j=0;j<g.vexnum;j++)
			A[i][j]=0;
	A[0][1]=1;A[0][2]=1;A[0][3]=1;A[0][4]=1;
	A[1][8]=1;A[3][6]=1;A[4][7]=1;A[5][8]=1;
	A[5][9]=1;A[6][7]=1;A[6][9]=1;A[7][10]=1;
	A[7][11]=1;A[8][12]=1;A[9][10]=1;A[9][12]=1;
	A[10][13]=1;A[11][13]=1;A[12][14]=1;A[13][14]=1;
	for (i=0;i<g.vexnum;i++)
		for (j=0;j<g.vexnum;j++)
			A[j][i]=A[i][j];
	for (i=0;i<g.vexnum;i++)		/*建立图图9.9的邻接矩阵*/
		for (j=0;j<g.vexnum;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g,G);
	for (i=0;i<g.vexnum;i++) 
		visited[i]=0;
	printf("\n 起点和终点:");
	scanf("%d%d",&u,&v);
	printf(" 必经点个数:");
	scanf("%d",&n);
	printf(" 必经点集合:");
	for (i=0;i<n;i++)
		scanf("%d",&V1[i]);
	printf(" 必避点个数:");
	scanf("%d",&m);
	printf(" 必避点集合:");
	for (i=0;i<m;i++)
		scanf("%d",&V2[i]);
	printf("\n 探宝路径:\n");
    TravPath(G,u,v,-1);printf("\n");
}