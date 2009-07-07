/*文件名:exp8-3.cpp*/
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct lnode  
{
	int tag;				/*结点类型标识*/
   	union 
	{	
		ElemType data;
        struct lnode *sublist;
	}val;
    struct lnode *link;		/*指向下一个元素*/
} GLNode;
extern GLNode *GLCopy(GLNode *p);	/*以下外部函数在algo8-2.cpp中*/
extern GLNode *head(GLNode *g);
extern GLNode *tail(GLNode *g);
extern GLNode *CreatGL(char *&s);	/*以下外部函数在algo8-1.cpp中*/
extern void DispGL(GLNode *g);
GLNode *Append(GLNode *gh,GLNode *gt)
{
	gh->link=gt->val.sublist;
	gt->val.sublist=gh;
	return(gt);
}
int AtomCount1(GLNode *g) 
{
    int num=0;
	if (g!=NULL)
	{
		if (g->tag==1)   /*为子表时,求其中的原子个数*/
			num+=AtomCount1(g->val.sublist);
		else             /*为原子时,返回1*/
			num+=1;
		num+=AtomCount1(g->link);
	}
	return num;
}
int AtomCount2(GLNode *g) 
{
	if (g->val.sublist==NULL)	/*为空表时返回0*/
		return(0);
	else if (g->tag==0)			/*为原子时返回1*/
		return(1);
	else						/*其他情况*/
		return(AtomCount2(head(g))+AtomCount2(tail(g)));
}
int GLLength1(GLNode *g)		/*求带头结点广义表g的长度*/
{
	GLNode *gt;
	if (g==NULL)
		return 0;
	else if (g->val.sublist==NULL)	/*空表时返回0*/
		return 0;
	else
	{
		gt=tail(g);
		return(GLLength1(gt)+1);
	}
}
int GLDepth1(GLNode *g) 	/*求带头结点广义表g的深度*/
{
	int maxdep,dep1,dep2;
	GLNode *gh,*gt;
	if (g==NULL)
		return 0;
	else if (g->tag==0)
		return 0;
	else if (g->val.sublist==NULL)	/*空表时返回1*/
		return 1;
	else
	{
		gh=head(g);
		dep1=GLDepth1(gh)+1;
		gt=tail(g);
		dep2=GLDepth1(gt);
		maxdep=(dep1>dep2 ? dep1 : dep2);
		return(maxdep);
	}
}
void main()
{
	GLNode *g,*gh,*gt,*g1;
	char *str1="((a),((b)),((((c)))),d)";
	g=CreatGL(str1);
	printf("\n");
	printf("  广义表g:");DispGL(g);printf("\n");
	gh=head(g);
	printf("    g表头:");DispGL(gh);
	gt=tail(g);
	printf("    g表尾:");DispGL(gt);printf("\n\n");
	g1=Append(gh,gt);
	printf("  广义表g:");DispGL(g);printf("\n");
	printf("  广义表g的原子数:%d\n",AtomCount1(g));
	printf("  广义表g的原子数:%d\n\n",AtomCount2(g));
	printf("  广义表g的长度:%d\n",GLLength1(g));
	printf("  广义表g的深度:%d\n",GLDepth1(g));
	printf("\n");
}