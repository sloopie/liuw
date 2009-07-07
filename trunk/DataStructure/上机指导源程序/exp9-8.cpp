/文件名:exp9-8.cpp*/
#include <stdio.h>
#include "graph.h"
#define	MAXV  100				/*最大顶点个数*/
#define INF 32767               /*用32767表示∞*/
extern void DispMat(MGraph g);	/*外部函数在algo9-1.c*/
void ppath(int path[],int i,int v0) 
{
	int k;
	k=path[i];
	if (k==v0)  return;
	ppath(path,k,v0);
	printf("%d,",k);
}
void DisPath(int dist[],int path[],int s[],int n,int v0) /*由path计算最短路径*/
{
	int i;
	printf("  path:");		/*输出path值*/
	for (i=0;i<n;i++)
		printf("%3d",path[i]);
	printf("\n");
	for (i=0;i<n;i++)
		if (s[i]==1 && i!=v0) 
		{	
		  	printf("  从%d到%d的最短路径长度为:%d\t路径为:",v0,i,dist[i]);
			printf("%d,",v0);ppath(path,i,v0);printf("%d\n",i);
		}
		else  
			printf("  从%d到%d不存在路径\n",v0,i);
}
void Dijkstra(MGraph g,int v0)	/*狄克斯特拉算法从顶点v0到其余各顶点的最短路径*/
{
	int dist[MAXV],path[MAXV];
	int s[MAXV];
	int mindis,i,j,u,n=g.vexnum;
	for (i=0;i<n;i++) 
	{	
		dist[i]=g.edges[v0][i];   			/*距离初始化*/
		s[i]=0;                			/*s[]置空*/
		if (g.edges[v0][i]<INF)			/*路径初始化*/
			path[i]=v0;
		else
		    path[i]=-1;
	}
	s[v0]=1;path[v0]=0;        			/*源点编号v0放入s中*/
	for (i=0;i<n;i++)     				/*循环直到所有顶点的最短路径都求出*/
	{	
		mindis=INF;
		u=-1;
		for (j=0;j<n;j++)     			/*选取不在s中且具有最小距离的顶点u*/
			if (s[j]==0 && dist[j]<mindis) 
			{ 	
				u=j;mindis=dist[j];	
			}
		s[u]=1;               			/*顶点u加入s中*/
		for (j=0;j<n;j++)      			/*修改不在s中的顶点的距离*/
			if (s[j]==0) 
				if (g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j]) 
				{	
					dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}  
	}
	printf("输出最短路径:\n");
	DisPath(dist,path,s,n,v0);  		/*输出最短路径*/
}
void main()
{
	int i,j,u=0;
	MGraph g;
	int A[MAXV][6]={
		{INF,5,INF,7,INF,INF},
		{INF,INF,4,INF,INF,INF},
		{8,INF,INF,INF,INF,9},
		{INF,INF,5,INF,INF,6},
		{INF,INF,INF,5,INF,INF},
		{3,INF,INF,INF,1,INF}};
	g.vexnum=6;g.arcnum=10;
	for (i=0;i<g.vexnum;i++)		/*建立图9.1的邻接矩阵*/
		for (j=0;j<g.vexnum;j++)
			g.edges[i][j]=A[i][j];
	printf("\n");
	printf("有向图G的邻接矩阵:\n");
	DispMat(g);
	Dijkstra(g,u);
	printf("\n");
}
