/*�ļ���:exp8-4.cpp*/
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
extern GLNode *CreatGL(char *&s);	/*�����ⲿ������algo8-1.cpp��*/
extern void DispGL(GLNode *g);
void Change(GLNode *&g,ElemType s,ElemType t) /*�������g������ԭ��s�滻��t*/
{
	if (g!=NULL)
	{
		if (g->tag==1)				/*�ӱ�����*/
			Change(g->val.sublist,s,t);
		else if (g->val.data==s)	/*ԭ����data��ֵΪs�����*/
			g->val.data=t;
		Change(g->link,s,t);
	}
}
void Reverse(GLNode *&g)	/*�������g����Ԫ������*/
{
	GLNode *p,*q,*t;
	t=NULL;
	if (g!=NULL) 
	{
		p=g;
		while (p!=NULL)		/*��ͬ�����ֵ�����*/
		{
			q=p->link;
			if (t==NULL)
			{
				t=p;
				p->link=NULL;
			}
			else
			{
				p->link=t;
				t=p;
			}
			p=q;
		}
		g=t;
		p=g;
		while (p!=NULL)
		{
			if (p->tag==1)
				Reverse(p->val.sublist);
			p=p->link;
		}
	}
}
int Same(GLNode *g1,GLNode *g2)	/*�ж�����������Ƿ���ͬ*/
{
    int s;
    if (g1==NULL && g2==NULL)      /*��ΪNULL�����*/
		return 1;
	else if ((g1==NULL && g2!=NULL) || (g1!=NULL && g2==NULL)) /*һ��ΪNULL,��һ��ΪNULL�����*/
		return 0;
	else
	{
		s=1;
		while (g1!=NULL && g2!=NULL && s==1) 
		{
			if (g1->tag==1 && g2->tag==1)			/*��Ϊ�ӱ�����*/
				s=Same(g1->val.sublist,g2->val.sublist);
			else if (g1->tag==0 && g2->tag==0)		/*��Ϊԭ�ӵ����*/
			{ 
				if (g1->val.data!=g2->val.data)
					s=0;
			}
			else       /*һ��Ϊԭ��,��һΪ�ӱ�����*/
				s=0;
			g1=g1->link;
			g2=g2->link;
		}
		if (g1!=NULL || g2!=NULL)	/*��һ���ӱ���δ�Ƚ���ʱ*/
			s=0;
		return s;
	}
}
ElemType MaxAtom(GLNode *g)	/*������g������ԭ��*/
{
    ElemType m=0,m1;						/*m����ֵ0*/
    while (g!=NULL) 
	{ 
       if (g->tag==1)          				/*�ӱ�����*/
	   {
		   m1=MaxAtom(g->val.sublist); 		/*���ӱ�ݹ����*/
           if (m1>m) m=m1;
	   }
       else 
	   {
		   if (g->val.data>m)    			/*Ϊԭ��ʱ,����ԭ�ӱȽ�*/
              m=g->val.data;
	   }
       g=g->link;
	}
    return m;
}
void DelAtom(GLNode *&g,ElemType x)	/*ɾ�������g�еĵ�һ��Ϊxԭ��*/
{
	GLNode *p=g,*q,*pre;
    while (p!=NULL) 
	{ 
		q=p->link;
		if (p->tag==1)          			/*�ӱ�����*/
			DelAtom(p->val.sublist,x); 	/*���ӱ�ݹ����*/
		else 
		{
		   if (p->val.data==x)    			/*Ϊԭ��ʱ,����ԭ�ӱȽ�*/
		   {
			   if (p==g)					/*��ɾ����Ǳ���ĵ�1�����*/
			   {
				   g=q;
				   free(p);					/*�ͷŽ��*/
				   pre=g;
			   }
			   else							/*��ɾ��㲻�Ǳ���ĵ�1�����,preΪ��ǰ��*/
			   {
				   pre->link=q;
				   free(p);
			   }
			   return;
		   }
		}
		pre=p;
		p=q;
	}
}
void DelAtomAll(GLNode *&g,ElemType x)	/*ɾ�������g�е�����Ϊxԭ��*/
{
	GLNode *p=g,*q,*pre;
    while (p!=NULL) 
	{ 
		q=p->link;
		if (p->tag==1)          			/*�ӱ�����*/
			DelAtomAll(p->val.sublist,x); 	/*���ӱ�ݹ����*/
		else 
		{
		   if (p->val.data==x)    			/*Ϊԭ��ʱ,����ԭ�ӱȽ�*/
			   if (p==g)					/*��ɾ����Ǳ���ĵ�1�����*/
			   {
				   g=q;
				   free(p);					/*�ͷŽ��*/
				   pre=g;
			   }
			   else							/*��ɾ��㲻�Ǳ���ĵ�1�����,preΪ��ǰ��*/
			   {
				   pre->link=q;
				   free(p);
			   }
		}
		pre=p;
		p=q;
	}
}
void PreOrder(GLNode *g)	/*�����ȸ�����g*/
{
	if (g!=NULL)
	{
		if (g->tag==0)					/*Ϊԭ�ӽ��ʱ*/
			printf("%c ",g->val.data);
		else
			PreOrder(g->val.sublist);	/*Ϊ�ӱ�ʱ*/
		PreOrder(g->link);
	}
}
void main()
{
	GLNode *g1,*g2,*g3,*g4;
	char *str1="(a,(a),((a,b)),((a)),a)";
	char *str2="(a,(b),((c,d)),((e)),f)";
	char *str3="(a,(a,b),(a,b,c)))";
	char *str4="(a,(b),((c,d)),((e)),f)";
	g1=CreatGL(str1);
	printf("\n");
	printf("  �����g1:");DispGL(g1);printf("\n");
	printf("  �������g1������'a'��Ϊ'b'\n");
	Change(g1,'a','b');
	printf("  �����g1:");DispGL(g1);printf("\n\n");

	g2=CreatGL(str2);
	printf("  �����g2:");DispGL(g2);printf("\n");
	printf("  �����g2�����ԭ��:%c\n",MaxAtom(g2));
	printf("  ��g2��Ԫ������\n");
	Reverse(g2);
	printf("  �����g2:");DispGL(g2);printf("\n\n");
	printf("  �����g1��g2%s\n\n",(Same(g1,g2)?"��ͬ":"����ͬ"));

	g3=CreatGL(str3);
	printf("  �����g3:");DispGL(g3);printf("\n");
	printf("  ɾ�������g3�ĵ�һ��Ϊ'a'��ԭ��\n");
	DelAtom(g3,'a');
	printf("  �����g3:");DispGL(g3);printf("\n\n");
	
	printf("  ɾ�������g3�е�����'a'ԭ��\n");
	DelAtomAll(g3,'a');
	printf("  �����g3:");DispGL(g3);printf("\n\n");

	g4=CreatGL(str4);
	printf("  �����g4:");DispGL(g4);printf("\n");
	printf("  �����ȸ�����g4�Ľ��:");
	PreOrder(g4);
	printf("\n\n");
}