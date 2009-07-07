/*文件名:algo2-4.cpp*/
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct LNode		/*定义单链表结点类型*/
{
	ElemType data;
    struct LNode *next;
} LinkList;
void InitList(LinkList *&L)
{
	L=(LinkList *)malloc(sizeof(LinkList));	/*创建头结点*/
	L->next=L;
}
void DestroyList(LinkList *&L)
{
	LinkList *p=L,*q=p->next;
	while (q!=L)
	{
		free(p);
		p=q;
		q=p->next;
	}
	free(p);
}
int ListEmpty(LinkList *L)
{
	return(L->next==L);
}
int ListLength(LinkList *L)
{
	LinkList *p=L;int i=0;
	while (p->next!=L)
	{
		i++;
		p=p->next;
	}
	return(i);
}
void DispList(LinkList *L)
{
	LinkList *p=L->next;
	while (p!=L)
	{
		printf("%c",p->data);
		p=p->next;
	}
	printf("\n");
}
int GetElem(LinkList *L,int i,ElemType &e)
{
	int j=0;
	LinkList *p;
	if (L->next!=L)		/*单链表不为空表时*/
	{
		if (i==1)
		{
			e=L->next->data;
			return 1;
		}
		else			/*i不为1时*/
		{
			p=L->next;
			while (j<i-1 && p!=L)
			{
				j++;
				p=p->next;
			}
			if (p==L)
				return 0;
			else
			{
				e=p->data;
				return 1;
			}
		}
	}
	else				/*单链表为空表时*/
		return 0;
}
int LocateElem(LinkList *L,ElemType e)
{
	LinkList *p=L->next;
	int n=1;
	while (p!=L && p->data!=e)
	{
		p=p->next;
		n++;
	}
	if (p==L)
		return(0);
	else
		return(n);
}
int ListInsert(LinkList *&L,int i,ElemType e)
{
	int j=0;
	LinkList *p=L,*s;
	if (p->next==L || i==1)		/*原单链表为空表或i==1时*/
	{
		s=(LinkList *)malloc(sizeof(LinkList));	/*创建新结点*s*/
		s->data=e;								
		s->next=p->next;		/*将*s插入到*p之后*/
		p->next=s;
		return 1;
	}
	else
	{
		p=L->next;
		while (j<i-2 && p!=L)
		{
			j++;
			p=p->next;
		}
		if (p==L)				/*未找到第i-1个结点*/
			return 0;
		else					/*找到第i-1个结点*p*/
		{
			s=(LinkList *)malloc(sizeof(LinkList));	/*创建新结点*s*/
			s->data=e;								
			s->next=p->next;						/*将*s插入到*p之后*/
			p->next=s;
			return 1;
		}
	}
}
int ListDelete(LinkList *&L,int i,ElemType &e)
{
	int j=0;
	LinkList *p=L,*q;
	if (p->next!=L)					/*原单链表不为空表时*/
	{
		if (i==1)					/*i==1时*/
		{
			q=L->next;				/*删除第1个结点*/
			L->next=q->next;
			free(q);
			return 1;
		}
		else						/*i不为1时*/
		{
			p=L->next;
			while (j<i-2 && p!=L)
			{
				j++;
				p=p->next;
			}
			if (p==L)				/*未找到第i-1个结点*/
				return 0;
			else					/*找到第i-1个结点*p*/
			{
				q=p->next;			/*q指向要删除的结点*/
				p->next=q->next;	/*从单链表中删除*q结点*/
				free(q);			/*释放*q结点*/
				return 1;
			}
		}
	}
	else return 0;
}
