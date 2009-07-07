/*文件名:exp3-5.cpp*/
#include <stdio.h>
#define M 6					/*行数*/
#define N 6					/*列数*/
#define MaxSize 100			/*栈最多元素个数*/
int mg[M+1][N+1]={			/*一个迷宫,其四周要加上均为1的外框*/
{1,1,1,1,1,1},
{1,0,0,0,1,1},
{1,0,1,0,0,1},
{1,0,0,0,1,1},
{1,1,0,0,0,1},
{1,1,1,1,1,1}
};
struct 
{
	int i;int j;int di;
} Stack[MaxSize],Path[MaxSize];	/*定义栈和存放最短路径的数组*/
int top=-1;						/*栈指针*/
int count=1;					/*路径数计数*/
int minlen=MaxSize;				/*最短路径长度*/
void mgpath()					/*路径为:(1,1)->(M-2,N-2)*/
{
	int i,j,di,find,k;
	top++;						/*进栈*/
	Stack[top].i=1;
	Stack[top].j=1;
	Stack[top].di=-1;mg[1][1]=-1; /*初始结点进栈*/
	while (top>-1)				/*栈不空时循环*/
	{
		i=Stack[top].i;j=Stack[top].j;di=Stack[top].di;
		if (i==M-2 && j==N-2)	/*找到了出口,输出路径*/
		{ 
			printf("%4d:   ",count++);
			for (k=0;k<=top;k++)
			{
				printf("(%d,%d)    ",Stack[k].i,Stack[k].j);
				if ((k+1)%5==0) printf("\n\t");  /*输出时每5个结点换一行*/
			}
			printf("\n");
			if (top+1<minlen)					/*比较找最短路径*/
			{
				for (k=0;k<=top;k++)
					Path[k]=Stack[k];
				minlen=top+1;
			}
			mg[Stack[top].i][Stack[top].j]=0;    /*让该位置变为其他路径可走结点*/
			top--; 
			i=Stack[top].i;j=Stack[top].j;di=Stack[top].di;
		}
		find=0;
		while (di<4 && find==0) /*找下一个可走结点*/
		{	di++;
			switch(di)
			{
			case 0:i=Stack[top].i-1;j=Stack[top].j;break;
			case 1:i=Stack[top].i;j=Stack[top].j+1;break;
			case 2:i=Stack[top].i+1;j=Stack[top].j;break;
			case 3:i=Stack[top].i,j=Stack[top].j-1;break;
			}
			if (mg[i][j]==0) find=1;
		}
		if (find==1)				/*找到了下一个可走结点*/
		{	Stack[top].di=di;		/*修改原栈顶元素的di值*/
			top++;Stack[top].i=i;Stack[top].j=j;Stack[top].di=-1;/*下一个可走结点进栈*/
			mg[i][j]=-1;			/*避免重复走到该结点*/
		}
		else						/*没有路径可走,则退栈*/
		{
			mg[Stack[top].i][Stack[top].j]=0;    /*让该位置变为其他路径可走结点*/
			top--;
		}
	}
	printf("最短路径如下:\n");
	printf("长度:   %d\n",minlen);
	printf("路径:   ");
	for (k=0;k<minlen;k++)
	{
		printf("(%d,%d)   ",Path[k].i,Path[k].j);
		if ((k+1)%5==0) printf("\n\t");  /*输出时每5个结点换一行*/
	}
	printf("\n");
}
void main()
{
	printf("迷宫所有路径如下:\n");
	mgpath();
}
