#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAXWORD 100
typedef struct tnode 
{
	char ch;
	int count;
	struct tnode *lchild,*rchild;
} BTree;

void CreaTree(BTree *&p,char c)
{
	if (p==NULL)
	{
		p=(BTree *)malloc(sizeof(BTree));
		p->ch=c;
		p->count=1;
		p->lchild=p->rchild=NULL;
	}
	else if (c==p->ch) 
		p->count++;
	else if (c<p->ch) 
		CreaTree(p->lchild,c);
	else 
		CreaTree(p->rchild,c);
}

void InOrder(BTree *p)	
{
	if (p!=NULL) 
	{
		InOrder(p->lchild);
		printf("  %c(%d)\n",p->ch,p->count);
		InOrder(p->rchild);
	}
}

void main()
{
	BTree *root=NULL;
	int i=0;
	char str[MAXWORD];
	printf("\n");
	printf("Input string:");
	gets(str);
	while (str[i]!='\0') 
	{
		CreaTree(root,str[i]);
		i++;
	}
	printf("words and counts:\n");
	InOrder(root);
	printf("\n");
}
