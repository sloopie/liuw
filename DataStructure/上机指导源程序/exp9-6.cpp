/*文件名:exp9-6.cpp*/
#include <stdio.h>
#include "graph.h"
#define INF 32767       /*INF表示∞*/
extern void DispMat(MGraph);	/*外部函数在algo9-1.cpp中*/
void prim(MGraph g,int v)
{
	int lowcost[MAXV],min,n=g.vexnum;
	int closest[MAXV],i,j,k;
	for (i=0;i<n;i++)          	/*给lowcost[]和closest[]置初值*/
	{	
		lowcost[i]=g.edges[v][i];
		closest[i]=v;
	}
	for (i=1;i<n;i++)          	/*找出n-1个顶点*/
	{   
		min=INF;
	    for (j=0;j<n;j++)       /*在(V-U)中找出离U最近的顶点k*/
		   	if (lowcost[j]!=0 && lowcost[j]<min) 
			{	
				min=lowcost[j];k=j;  
			}
		printf("  边(%d,%d)权为:%d\n",closest[k],k,min);
		lowcost[k]=0;         	/*标记k已经加入U*/
		for (j=0;j<n;j++)   	/*修改数组lowcost和closest*/
           	if (g.edges[k][j]!=0 && g.edges[k][j]<lowcost[j]) 
			{	
				lowcost[j]=g.edges[k][j];closest[j]=k; 
			}
	}
}
void main()
{
	int i,j,u=3;
	MGraph g;
	int A[MAXV][11];
	g.vexnum=6;g.arcnum=10;
	for (i=0;i<g.vexnum;i++)
		for (j=0;j<g.vexnum;j++)
			A[i][j]=INF;
	A[0][1]=5;A[0][2]=8;A[0][3]=7;A[0][5]=3;
	A[1][2]=4;
	A[2][3]=5;A[2][5]=9;
	A[3][4]=5;
	A[4][5]=1;
	for (i=0;i<g.vexnum;i++)
		for (j=0;j<g.vexnum;j++)
			A[j][i]=A[i][j];
	for (i=0;i<g.vexnum;i++)		/*建立图9.15的邻接矩阵*/
		for (j=0;j<g.vexnum;j++)
			g.edges[i][j]=A[i][j];
	printf("\n");
	printf("图G的邻接矩阵:\n");
	DispMat(g);
	printf("\n");
	printf("普里姆算法求解结果:\n");
	prim(g,0);
	printf("\n");
}
