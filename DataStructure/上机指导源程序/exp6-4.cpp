/*文件名:exp6-4.cpp*/
#include <stdio.h>
#define MaxSize 100
int fun1(int n)
{
    int f;
    if (n==0) 
		return(1);
    else 
	{
        f=fun1(n/2);
        return(n*f);
    }
}
int fun2(int n)
{
	int i=1,f=1;
	while (n>0)
	{
		f=n*f;
		n=n/2;
	}
	return(f);
}
int fun3(int n)
{
	struct 
	{
		int vn;			/*保存n值*/
		int vf;			/*保存fun3(n)值*/
		int tag;		/*标识是否求出fun3(n)值,1:未求出,0:已求出*/
	} St[MaxSize];		/*定义栈*/
	int top=-1;
	top++;								/*初值进栈*/
	St[top].vn=n;St[top].tag=1;
	while (top>-1)						/*栈不空时循环*/
	{
		if (St[top].tag==1)				/*未计算出栈顶元素的vf值*/
		{	
			if (St[top].vn==0)			/*(1)式*/
			{	St[top].vf=1;
				St[top].tag=0;
			}
			else 						/*(2)式*/
			{	
				top++;
				St[top].vn=St[top-1].vn/2;
				St[top].tag=1;
			}
		}
		else if (St[top].tag==0)		/*已计算出vf值*/
		{	
			if (St[top-1].vn>0)			/*(2)式*/
			{
				St[top-1].vf=St[top-1].vn*St[top].vf;
				St[top-1].tag=0;
				top--;
			}
		}
		if (top==0 && St[top].tag==0)	/*栈中只有一个已求出vf的元素时退出循环*/
			break;
	} 
	return St[top].vf;
}

void main()
{
	int n=12;
	printf(" 各种方法求解结果如下:\n");
	printf("   fun1(%d)=%d\n",n,fun1(n));
	printf("   fun2(%d)=%d\n",n,fun2(n));
	printf("   fun3(%d)=%d\n",n,fun3(n));
}