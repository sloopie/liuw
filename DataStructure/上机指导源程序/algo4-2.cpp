/*文件名:algo4-2.cpp*/
#include <stdio.h>
#include <malloc.h>
typedef struct snode 
{
    char data;
    struct snode *next;
} LiString;
void StrAssign(LiString *&s,char t[])
{
    int i;
    LiString *r,*p;
    s=(LiString *)malloc(sizeof(LiString));
    s->next=NULL;r=s;
    for (i=0;t[i]!='\0';i++) 
	{    
		p=(LiString *)malloc(sizeof(LiString));
		p->data=t[i];p->next=NULL;
		r->next=p;r=p;
	}
}
void StrCopy(LiString *&s,LiString *t)
{
    LiString *p=t->next,*q,*r;
    s=(LiString *)malloc(sizeof(LiString));
    s->next=NULL;s->next=NULL;r=s;
    while (p!=NULL)      /*将t的所有结点复制到s*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
}
int StrEqual(LiString *s,LiString *t)
{
    LiString *p=s->next,*q=t->next;
    while (p!=NULL && q!=NULL && p->data==q->data) 
	{
        p=p->next;
        q=q->next;
    }
    if (p==NULL && q==NULL)
        return 1;
    else
        return 0;
}
int StrLength(LiString *s)
{
    int i=0;
    LiString *p=s->next;
    while (p!=NULL) 
	{
        i++;p=p->next;
    }
    return i;
}
LiString *Concat(LiString *s,LiString *t)
{
    LiString *str,*p=s->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    str->next=NULL;r=str;
    while (p!=NULL)     		/*将s的所有结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
    p=t->next;
    while (p!=NULL)     		/*将t的所有结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
    return str;
}
LiString *SubStr(LiString *s,int i,int j)
{
    int k;
    LiString *str,*p=s->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    str->next=NULL;r=str;
    if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
	{
		printf("参数不正确\n");
        return str;             	/*参数不正确时返回空串*/
	}
    for (k=0;k<i-1;k++)
        p=p->next;
    for (k=1;k<=j;k++)      		/*将s的第i个结点开始的j个结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
    return str;
}
LiString *InsStr(LiString *s,int i,LiString *t)
{
    int k;
    LiString *str,*p=s->next,*p1=t->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    str->next=NULL;r=str;
    if (i<=0 || i>StrLength(s)+1)      	/*参数不正确时返回空串*/
	{
		printf("参数不正确\n");
        return str;
	}
    for (k=1;k<i;k++)        			/*将s的前i个结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
    while (p1!=NULL)        		/*将t的所有结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p1->data;q->next=NULL;
        r->next=q;r=q;
        p1=p1->next;
    }
    while (p!=NULL)      		/*将*p及其后的结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
	return str;
}
LiString *DelStr(LiString *s,int i,int j)
{
    int k;
    LiString *str,*p=s->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    str->next=NULL;r=str;
    if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
	{
		printf("参数不正确\n");
        return str;               	/*参数不正确时返回空串*/
	}
	for (k=0;k<i-1;k++)      		/*将s的前i-1个结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
    for (k=0;k<j;k++)         		/*让p沿next跳j个结点*/
        p=p->next;
    while (p!=NULL)            		/*将*p及其后的结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
	return str;
}
LiString *RepStr(LiString *s,int i,int j,LiString *t)
{
    int k;
    LiString *str,*p=s->next,*p1=t->next,*q,*r;
    str=(LiString *)malloc(sizeof(LiString));
    str->next=NULL;r=str;
    if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
	{
		printf("参数不正确\n");
        return str;          		/*参数不正确时返回空串*/
	}
    for (k=0;k<i-1;k++)  			/*将s的前i-1个结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
    for (k=0;k<j;k++)   			/*让p沿next跳j个结点*/
        p=p->next;
    while (p1!=NULL)     			/*将t的所有结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p1->data;q->next=NULL;
        r->next=q;r=q;
        p1=p1->next;
    }
    while (p!=NULL)      			/*将*p及其后的结点复制到str*/
	{
        q=(LiString *)malloc(sizeof(LiString));
        q->data=p->data;q->next=NULL;
        r->next=q;r=q;
        p=p->next;
    }
	return str;
}
void DispStr(LiString *s)
{
    LiString *p=s->next;
    while (p!=NULL) 
	{
		printf("%c",p->data);
		p=p->next;
	}
	printf("\n");
}
