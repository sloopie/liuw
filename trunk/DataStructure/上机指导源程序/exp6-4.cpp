/*�ļ���:exp6-4.cpp*/
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
		int vn;			/*����nֵ*/
		int vf;			/*����fun3(n)ֵ*/
		int tag;		/*��ʶ�Ƿ����fun3(n)ֵ,1:δ���,0:�����*/
	} St[MaxSize];		/*����ջ*/
	int top=-1;
	top++;								/*��ֵ��ջ*/
	St[top].vn=n;St[top].tag=1;
	while (top>-1)						/*ջ����ʱѭ��*/
	{
		if (St[top].tag==1)				/*δ�����ջ��Ԫ�ص�vfֵ*/
		{	
			if (St[top].vn==0)			/*(1)ʽ*/
			{	St[top].vf=1;
				St[top].tag=0;
			}
			else 						/*(2)ʽ*/
			{	
				top++;
				St[top].vn=St[top-1].vn/2;
				St[top].tag=1;
			}
		}
		else if (St[top].tag==0)		/*�Ѽ����vfֵ*/
		{	
			if (St[top-1].vn>0)			/*(2)ʽ*/
			{
				St[top-1].vf=St[top-1].vn*St[top].vf;
				St[top-1].tag=0;
				top--;
			}
		}
		if (top==0 && St[top].tag==0)	/*ջ��ֻ��һ�������vf��Ԫ��ʱ�˳�ѭ��*/
			break;
	} 
	return St[top].vf;
}

void main()
{
	int n=12;
	printf(" ���ַ������������:\n");
	printf("   fun1(%d)=%d\n",n,fun1(n));
	printf("   fun2(%d)=%d\n",n,fun2(n));
	printf("   fun3(%d)=%d\n",n,fun3(n));
}