/*文件名:algo8-1.cpp*/
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
GLNode *CreatGL(char *&s)		/*由串s建立一个广义表*/
{	
	GLNode *h;
	char ch;
	ch=*s;                               	/*取一个扫描字符*/
	s++;                                	/*串指针后移一位*/
	if (ch!='\0')                       	/*串未结束判断*/
	{	
		h=(GLNode *)malloc(sizeof(GLNode));	/*创建一个新结点*/
        if (ch=='(')                   		/*当前字符为左括号时*/
		{	
			h->tag=1;                   	/*新结点作为表头结点*/
            h->val.sublist=CreatGL(s);   	/*递归构造子表并链到表头结点*/
		}
       	else if (ch==')') 
			h=NULL;           				/*遇到')'字符,子表为空*/
       	else
		{	
			h->tag=0;                   	/*新结点作为原子结点*/
            h->val.data=ch;
		}
	}
    else h=NULL;                          	/*串结束,子表为空*/
    ch=*s;                               	/*取下一个扫描字符*/
    s++;                                	/*串指针后移一位*/
    if (h!=NULL)                         	/*串未结束判断*/
       	if (ch==',')                     	/*当前字符为','*/
           	h->link=CreatGL(s);         	/*递归构造后续子表*/
       	else                               	/*串结束*/
           	h->link=NULL;                	/*处理表的最后一个元素*/
    return h;                              	/*返回广义表指针*/
}
int GLLength(GLNode *g)    	/*求广义表g的长度*/
{
	int n=0;
	g=g->val.sublist;		/*g指向广义表的第一个元素*/
    while (g!=NULL) 
	{	
		n++;
        g=g->link;
	}
    return n;
}
int GLDepth(GLNode *g) 		/*求带头结点的广义表g的深度*/
{
   	int max=0,dep;
	if (g->tag==0)
		return 0;
	g=g->val.sublist;				/*g指向第一个元素*/
	if  (g==NULL)					/*为空表时返回1*/
		return 1;
	while (g!=NULL)     			/*遍历表中的每一个元素*/
	{	
		if (g->tag==1)   			/*元素为子表的情况*/
		{	
			dep=GLDepth(g);			/*递归调用求出子表的深度*/
            if (dep>max) max=dep;	/*max为同一层所求过的子表中深度的最大值*/
		}
        g=g->link;  				/*使g指向下一个元素*/
	}
    return(max+1);    				/*返回表的深度*/
}
void DispGL(GLNode *g)  /*输出广义表g*/
{
	if (g!=NULL)                       				/*表不为空判断*/
	{	
		if (g->tag==1)               				/*为表结点时*/
		{
			printf("(");                 			/*输出'('*/
            if (g->val.sublist==NULL) printf("");  	/*输出空子表*/
            else DispGL(g->val.sublist);  			/*递归输出子表*/
		}
        else printf("%c", g->val.data);      		/*为原子时输出元素值*/
        if (g->tag==1) printf(")");               	/*为表结点时输出')'*/
        if (g->link!=NULL) 
		{	
			printf(",");
            DispGL(g->link);             			/*递归输出后续表的内容*/
		}
	}
}
