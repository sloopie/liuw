/*�ļ���:algo8-2.cpp*/
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct lnode  
{	int tag;				/*������ͱ�ʶ*/
   	union 
	{	
		ElemType data;
        struct lnode *sublist;
	}val;
    struct lnode *link;		/*ָ����һ��Ԫ��*/
} GLNode;
GLNode *GLCopy(GLNode *p)  /*pΪ�����ƵĹ�����ͷ���ָ��*/
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
GLNode *head(GLNode *h)  /*hΪһ��������ͷ���ָ��*/
{
	GLNode *p=h->val.sublist;
	GLNode *q,*t;
	if (p==NULL) 
	{	
		printf("�ձ������ͷ\n");
		return NULL;
	}
    else if (h->tag==0) 
	{	
		printf("ԭ�Ӳ������ͷ\n");
        return NULL;
	}
    if (p->tag==0)                	/*Ϊԭ�ӽ��ʱ*/
	{	
		q=(GLNode *)malloc(sizeof(GLNode));
        q->tag=0;q->val.data=p->val.data;
        q->link=NULL;
	}
	else 						/*Ϊ�ӱ�ʱ,�������ӱ�t*/
	{  	
		t=(GLNode *)malloc(sizeof(GLNode));
        t->tag=1;t->val.sublist=p->val.sublist;
        t->link=NULL;
        q=GLCopy(t);
        free(t);
	}
    return q;
}
GLNode *tail(GLNode *g)  /*gΪһ��������ͷ���ָ��*/
{
	GLNode *p=g->val.sublist;
	GLNode *q,*t;
	if (g==NULL) 							/*Ϊ�ձ�ʱ*/
	{   	
		printf("�ձ������β\n");
		return NULL;    	
	}
	else if (g->tag==0)               		/*Ϊԭ��ʱ*/
	{	
		printf("ԭ�Ӳ������β\n");
		return NULL;
	}
	p=p->link;
	t=(GLNode *)malloc(sizeof(GLNode)); 	/*����һ�����t*/
	t->tag=1;t->link=NULL;
	t->val.sublist=p;
	q=GLCopy(t);
	free(t);
	return q;
}
