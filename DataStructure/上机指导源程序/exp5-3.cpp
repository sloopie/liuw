/*ÎÄ¼şÃû:exp5-3.cpp*/
#include <stdio.h>
#define n 4
#define m 10
int value(int a[],int i,int j)
{
	if (i>=j)
		return a[(i*(i-1))/2+j];
	else
		return a[(j*(j-1))/2+i];
}
void madd(int a[],int b[],int c[n][n])
{
	int i,j;
    for (i=0;i<n;i++)
       for (j=0;j<n;j++)
           c[i][j]=value(a,i,j)+value(b,i,j);
}
void mult(int a[],int b[],int c[n][n])
{
	int i,j,k,s;
    for (i=0;i<n;i++)
       for (j=0;j<n;j++)
        {
		   s=0;
           for (k=0;k<n;k++)
			   s=s+value(a,i,k)*value(b,k,j);
           c[i][j]=s;
       }
}
void disp1(int a[])
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
			printf("%4d",value(a,i,j));
		printf("\n");
	}
}
void disp2(int c[n][n])
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
			printf("%4d",c[i][j]);
		printf("\n");
	}
}
void main()
{
	int a[m]={1,2,3,4,5,6,7,8,9,10};
	int b[m]={1,1,1,1,1,1,1,1,1,1};
	int c1[n][n],c2[n][n];
	madd(a,b,c1);
	mult(a,b,c2);
	printf("\n");
	printf("a¾ØÕó:\n");disp1(a);
	printf("b¾ØÕó:\n");disp1(b);
    printf("a+b:\n");disp2(c1);
    printf("a*b:\n");disp2(c2);
	printf("\n");
}
