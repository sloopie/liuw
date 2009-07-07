/*文件名：exp1-1.cpp*/
#include <stdio.h>
#include <math.h>
int prime(int x)	/*判断正整数x是否为素数*/
{
	int i;
	for (i=2;i<(int)sqrt(x);i++)
		if (x%i==0) return 0;		/*若x不是素数,则退出并返回0*/
	return 1;
}
void main()
{
	int n,i,j=0;	/*j用于累计素数个数*/
	printf("n:");
	scanf("%d",&n);
	printf("小于等于%d的素数:\n",n);
	if (n>2)
	{	printf("%4d",2);
		j++;
	}
	for (i=3;i<=n;i+=2)
		if (prime(i)==1)
		{	printf("%4d",i);
			if (j!=0 && ++j%10==0)	/*每行最多显示10个素数*/
				printf("\n");
		}
	printf("\n");
}
