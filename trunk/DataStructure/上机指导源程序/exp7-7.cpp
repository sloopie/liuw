/*文件名:exp7-7.cpp*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;				/*数据元素*/
	struct node *lchild;		/*指向左孩子*/
	struct node *rchild;		/*指向右孩子*/
} BTNode;
extern void DispBTNode(BTNode *b);	 /*在algo7-1.cpp文件中*/
BTNode *CRTree(char s[],int i,int j)
{
	BTNode *p;
	int k,plus=0,posi;
	if (i==j)
	{
		p=(BTNode *)malloc(sizeof(BTNode));
		p->data=s[i];
		p->lchild=NULL;
		p->rchild=NULL;
		return p;
	}
	/*以下为i!=j的情况*/
	for (k=i;k<=j;k++)
		if (s[k]=='+' || s[k]=='-')
		{
			plus++;
			posi=k;              /*最后一个+或-的位置*/
		}
	if (plus==0)                 /*没有+或-的情况*/
		for (k=i;k<=j;k++)
			if (s[k]=='*' || s[k]=='/')
			{
				plus++;
				posi=k;
			}
	p=(BTNode *)malloc(sizeof(BTNode));
	p->data=s[posi];
	p->lchild=CRTree(s,i,posi-1);
	p->rchild=CRTree(s,posi+1,j);
	return p;
}
void main()
{
	BTNode *b;
	char s[MaxSize]="a+b*c-e/f";
	printf("\n");
	printf(" 代数表达式%s\n",s);
	b=CRTree(s,0,strlen(s)-1);
	printf(" 对应二叉树:");
	DispBTNode(b);
	printf("\n\n");
}
