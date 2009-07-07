/*文件名:exp9-7.cpp*/
#include <stdio.h>
#include "graph.h"
#define INF 32767       /*INF表示∞*/
#define MAXE 100		/*最多边数*/
typedef struct 
{	int u;				/*边的起始顶点*/
    int v;				/*边的终止顶点*/
    int w;				/*边的权值*/		
} Edge;
extern void DispMat(MGraph);		/*外部函数在algo9-1.cpp中*/
void SortEdge(MGraph g,Edge E[])	/*从邻接矩阵产生权值递增的边集*/
{
	int i,j,k=0;
	Edge temp;
	for (i=0;i<g.vexnum;i++)
		for (j=0;j<g.vexnum;j++)
			if (g.edges[i][j]<INF)
			{
				E[k].u=i;
				E[k].v=j;
				E[k].w=g.edges[i][j];
				k++;
			}
	for (i=1;i<k;i++)	/*按权值递增有序进行直接插入排序*/ 
	{
		temp=E[i];
		j=i-1;			/*从右向左在有序区E[0..i-1]中找E[i]的插入位置*/
		while (j>=0 && temp.w<E[j].w) 
		{ 	
			E[j+1]=E[j]; /*将权值大于E[i].w的记录后移*/
			j--;
		}
		E[j+1]=temp;      /*在j+1处插入E[i]*/
	}
}
void Kruskal(Edge E[],int n,int e)
{
	int i,j,m1,m2,sn1,sn2,k;
	int vset[MAXE];
	for (i=0;i<n;i++) vset[i]=i;	/*初始化辅助数组*/
	k=1;                 			/*k表示当前构造最小生成树的第几条边,初值为1*/
	j=0;                 			/*E中边的下标,初值为0*/
	while (k<n)       				/*生成的边数小于n时循环*/
	{	
		m1=E[j].u;m2=E[j].v;        /*取一条边的头尾顶点*/
		sn1=vset[m1];sn2=vset[m2]; 	/*分别得到两个顶点所属的集合编号*/
		if (sn1!=sn2)     			/*两顶点属于不同的集合,该边是最小生成树的一条边*/
		{	
			printf("  (%d,%d):%d\n",m1,m2,E[j].w);
			k++;                    /*生成边数增1*/
			for (i=0;i<n;i++)      	/*两个集合统一编号*/
				if (vset[i]==sn2)  	/*集合编号为sn2的改为sn1*/
				    vset[i]=sn1;
		}
		j++;   						/*扫描下一条边*/
	}
}
void main()
{
	int i,j,u=3;
	MGraph g;
	Edge E[MAXE];
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
	SortEdge(g,E);
	printf("\n");
	printf("图G的邻接矩阵:\n");
	DispMat(g);
	printf("\n");
	printf("克鲁斯卡尔算法求解结果:\n");
	Kruskal(E,g.vexnum,g.arcnum);
	printf("\n");
}
