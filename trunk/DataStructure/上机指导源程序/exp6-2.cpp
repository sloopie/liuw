/*文件名:exp6-2.cpp*/
#include <stdio.h>
#include <stdlib.h>
const int N=20;      	/*最多皇后个数*/
int q[N];            		/*存放各皇后所在的行号*/
int cont=0;          		/*存放解个数*/
void print(int n)    	/*输出一个解*/
{
	cont++;
	int i;
	printf("  第%d个解：",cont);
	for (i=1;i<=n;i++)
		printf("%d ",q[i]);
	printf("\n");
}
int find(int i,int k) 	/*测试第k列的i行上能否摆放皇后*/
{
	int j;
	j=1;
	while (j<k)       	/*j=1～k-1是已放置了皇后的列*/
	{
	    if ((q[j]==i) || (abs(q[j]-i)==abs(j-k)))
            /*第j列皇后是否在i行或(q[j],j)与(i,k)是否同对角线*/
		    return 0;
	    j++;
	}
	return 1;
}
void place(int k,int n) /*第k个皇后放到第k列上*/
{
	if (k>n) 
		print(n);         		/*所有皇后放置结束*/
	else
		for (int i=1;i<=n;i++) 	/*在第k列上穷举每一个位置*/
		    if (find(i,k))  
			{
				q[k]=i;place(k+1,n);
     		}
}
void main()
{
	int n;     					/*n存放实际皇后个数*/
	printf(" 皇后问题(n<20) n=");
	scanf("%d",&n);
	if (n>20)
		printf("n值太大,不能求解\n");
	else
	{
		printf(" %d皇后问题求解如下：\n",n);
		place(1,n);
		printf("\n");
    }
}
