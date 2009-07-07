/*文件名:algo8-2.cpp*/
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct lnode  
{	int tag;				/*结点类型标识*/
   	union 
	{	
		ElemType data;
        struct lnode *sublist;
	}val;
    struct lnode *link;		/*指向下一个元素*/
} GLNode;
GLNode *GLCopy(GLNode *p)  /*p为被复制的广义表的头结点指针*/
{
	GLNode *q;
	if (p==NULL) return NULL;
	q=(GLNode *)malloc(sizeof(GLNode));
	q->tag=p->tag;
	if (p->tag==1)
		q->val.sublist=GLCopy(p->val.sublist);
	else
		q->val.data=p->val.data;
	q->link=GLCopy(p->link);
    return q;
}
GLNode *head(GLNode *h)  /*h为一个广义表的头结点指针*/
{
	GLNode *p=h->val.sublist;
	GLNode *q,*t;
	if (p==NULL) 
	{	
		printf("空表不能求表头\n");
		return NULL;
	}
    else if (h->tag==0) 
	{	
		printf("原子不能求表头\n");
        return NULL;
	}
    if (p->tag==0)                	/*为原子结点时*/
	{	
		q=(GLNode *)malloc(sizeof(GLNode));
        q->tag=0;q->val.data=p->val.data;
        q->link=NULL;
	}
	else 						/*为子表时,产生虚子表t*/
	{  	
		t=(GLNode *)malloc(sizeof(GLNode));
        t->tag=1;t->val.sublist=p->val.sublist;
        t->link=NULL;
        q=GLCopy(t);
        free(t);
	}
    return q;
}
GLNode *tail(GLNode *g)  /*g为一个广义表的头结点指针*/
{
	GLNode *p=g->val.sublist;
	GLNode *q,*t;
	if (g==NULL) 							/*为空表时*/
	{   	
		printf("空表不能求表尾\n");
		return NULL;    	
	}
	else if (g->tag==0)               		/*为原子时*/
	{	
		printf("原子不能求表尾\n");
		return NULL;
	}
	p=p->link;
	t=(GLNode *)malloc(sizeof(GLNode)); 	/*建立一个虚表t*/
	t->tag=1;t->link=NULL;
	t->val.sublist=p;
	q=GLCopy(t);
	free(t);
	return q;
}
