/*文件名:exp8-4.cpp*/
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
extern GLNode *CreatGL(char *&s);	/*以下外部函数在algo8-1.cpp中*/
extern void DispGL(GLNode *g);
void Change(GLNode *&g,ElemType s,ElemType t) /*将广义表g中所有原子s替换成t*/
{
	if (g!=NULL)
	{
		if (g->tag==1)				/*子表的情况*/
			Change(g->val.sublist,s,t);
		else if (g->val.data==s)	/*原子且data域值为s的情况*/
			g->val.data=t;
		Change(g->link,s,t);
	}
}
void Reverse(GLNode *&g)	/*将广义表g所有元素逆置*/
{
	GLNode *p,*q,*t;
	t=NULL;
	if (g!=NULL) 
	{
		p=g;
		while (p!=NULL)		/*将同级的兄弟逆置*/
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
int Same(GLNode *g1,GLNode *g2)	/*判断两个广义表是否相同*/
{
    int s;
    if (g1==NULL && g2==NULL)      /*均为NULL的情况*/
		return 1;
	else if ((g1==NULL && g2!=NULL) || (g1!=NULL && g2==NULL)) /*一个为NULL,另一不为NULL的情况*/
		return 0;
	else
	{
		s=1;
		while (g1!=NULL && g2!=NULL && s==1) 
		{
			if (g1->tag==1 && g2->tag==1)			/*均为子表的情况*/
				s=Same(g1->val.sublist,g2->val.sublist);
			else if (g1->tag==0 && g2->tag==0)		/*均为原子的情况*/
			{ 
				if (g1->val.data!=g2->val.data)
					s=0;
			}
			else       /*一个为原子,另一为子表的情况*/
				s=0;
			g1=g1->link;
			g2=g2->link;
		}
		if (g1!=NULL || g2!=NULL)	/*有一个子表尚未比较完时*/
			s=0;
		return s;
	}
}
ElemType MaxAtom(GLNode *g)	/*求广义表g中最大的原子*/
{
    ElemType m=0,m1;						/*m赋初值0*/
    while (g!=NULL) 
	{ 
       if (g->tag==1)          				/*子表的情况*/
	   {
		   m1=MaxAtom(g->val.sublist); 		/*对子表递归调用*/
           if (m1>m) m=m1;
	   }
       else 
	   {
		   if (g->val.data>m)    			/*为原子时,进行原子比较*/
              m=g->val.data;
	   }
       g=g->link;
	}
    return m;
}
void DelAtom(GLNode *&g,ElemType x)	/*删除广义表g中的第一个为x原子*/
{
	GLNode *p=g,*q,*pre;
    while (p!=NULL) 
	{ 
		q=p->link;
		if (p->tag==1)          			/*子表的情况*/
			DelAtom(p->val.sublist,x); 	/*对子表递归调用*/
		else 
		{
		   if (p->val.data==x)    			/*为原子时,进行原子比较*/
		   {
			   if (p==g)					/*被删结点是本层的第1个结点*/
			   {
				   g=q;
				   free(p);					/*释放结点*/
				   pre=g;
			   }
			   else							/*被删结点不是本层的第1个结点,pre为其前驱*/
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
void DelAtomAll(GLNode *&g,ElemType x)	/*删除广义表g中的所有为x原子*/
{
	GLNode *p=g,*q,*pre;
    while (p!=NULL) 
	{ 
		q=p->link;
		if (p->tag==1)          			/*子表的情况*/
			DelAtomAll(p->val.sublist,x); 	/*对子表递归调用*/
		else 
		{
		   if (p->val.data==x)    			/*为原子时,进行原子比较*/
			   if (p==g)					/*被删结点是本层的第1个结点*/
			   {
				   g=q;
				   free(p);					/*释放结点*/
				   pre=g;
			   }
			   else							/*被删结点不是本层的第1个结点,pre为其前驱*/
			   {
				   pre->link=q;
				   free(p);
			   }
		}
		pre=p;
		p=q;
	}
}
void PreOrder(GLNode *g)	/*采用先根遍历g*/
{
	if (g!=NULL)
	{
		if (g->tag==0)					/*为原子结点时*/
			printf("%c ",g->val.data);
		else
			PreOrder(g->val.sublist);	/*为子表时*/
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
	printf("  广义表g1:");DispGL(g1);printf("\n");
	printf("  将广义表g1中所有'a'改为'b'\n");
	Change(g1,'a','b');
	printf("  广义表g1:");DispGL(g1);printf("\n\n");

	g2=CreatGL(str2);
	printf("  广义表g2:");DispGL(g2);printf("\n");
	printf("  广义表g2中最大原子:%c\n",MaxAtom(g2));
	printf("  将g2的元素逆置\n");
	Reverse(g2);
	printf("  广义表g2:");DispGL(g2);printf("\n\n");
	printf("  广义表g1和g2%s\n\n",(Same(g1,g2)?"相同":"不相同"));

	g3=CreatGL(str3);
	printf("  广义表g3:");DispGL(g3);printf("\n");
	printf("  删除广义表g3的第一个为'a'的原子\n");
	DelAtom(g3,'a');
	printf("  广义表g3:");DispGL(g3);printf("\n\n");
	
	printf("  删除广义表g3中的所有'a'原子\n");
	DelAtomAll(g3,'a');
	printf("  广义表g3:");DispGL(g3);printf("\n\n");

	g4=CreatGL(str4);
	printf("  广义表g4:");DispGL(g4);printf("\n");
	printf("  采用先根遍历g4的结果:");
	PreOrder(g4);
	printf("\n\n");
}