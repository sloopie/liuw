/*�ļ���:exp7-7.cpp*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;				/*����Ԫ��*/
	struct node *lchild;		/*ָ������*/
	struct node *rchild;		/*ָ���Һ���*/
} BTNode;
extern void DispBTNode(BTNode *b);	 /*��algo7-1.cpp�ļ���*/
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
	/*����Ϊi!=j�����*/
	for (k=i;k<=j;k++)
		if (s[k]=='+' || s[k]=='-')
		{
			plus++;
			posi=k;              /*���һ��+��-��λ��*/
		}
	if (plus==0)                 /*û��+��-�����*/
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
	printf(" �������ʽ%s\n",s);
	b=CRTree(s,0,strlen(s)-1);
	printf(" ��Ӧ������:");
	DispBTNode(b);
	printf("\n\n");
}
