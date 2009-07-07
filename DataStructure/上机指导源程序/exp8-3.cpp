/*�ļ���:exp8-3.cpp*/
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct lnode  
{
	int tag;				/*������ͱ�ʶ*/
   	union 
	{	
		ElemType data;
        struct lnode *sublist;
	}val;
    struct lnode *link;		/*ָ����һ��Ԫ��*/
} GLNode;
extern GLNode *GLCopy(GLNode *p);	/*�����ⲿ������algo8-2.cpp��*/
extern GLNode *head(GLNode *g);
extern GLNode *tail(GLNode *g);
extern GLNode *CreatGL(char *&s);	/*�����ⲿ������algo8-1.cpp��*/
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
		if (g->tag==1)   /*Ϊ�ӱ�ʱ,�����е�ԭ�Ӹ���*/
			num+=AtomCount1(g->val.sublist);
		else             /*Ϊԭ��ʱ,����1*/
			num+=1;
		num+=AtomCount1(g->link);
	}
	return num;
}
int AtomCount2(GLNode *g) 
{
	if (g->val.sublist==NULL)	/*Ϊ�ձ�ʱ����0*/
		return(0);
	else if (g->tag==0)			/*Ϊԭ��ʱ����1*/
		return(1);
	else						/*�������*/
		return(AtomCount2(head(g))+AtomCount2(tail(g)));
}
int GLLength1(GLNode *g)		/*���ͷ�������g�ĳ���*/
{
	GLNode *gt;
	if (g==NULL)
		return 0;
	else if (g->val.sublist==NULL)	/*�ձ�ʱ����0*/
		return 0;
	else
	{
		gt=tail(g);
		return(GLLength1(gt)+1);
	}
}
int GLDepth1(GLNode *g) 	/*���ͷ�������g�����*/
{
	int maxdep,dep1,dep2;
	GLNode *gh,*gt;
	if (g==NULL)
		return 0;
	else if (g->tag==0)
		return 0;
	else if (g->val.sublist==NULL)	/*�ձ�ʱ����1*/
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
	printf("  �����g:");DispGL(g);printf("\n");
	gh=head(g);
	printf("    g��ͷ:");DispGL(gh);
	gt=tail(g);
	printf("    g��β:");DispGL(gt);printf("\n\n");
	g1=Append(gh,gt);
	printf("  �����g:");DispGL(g);printf("\n");
	printf("  �����g��ԭ����:%d\n",AtomCount1(g));
	printf("  �����g��ԭ����:%d\n\n",AtomCount2(g));
	printf("  �����g�ĳ���:%d\n",GLLength1(g));
	printf("  �����g�����:%d\n",GLDepth1(g));
	printf("\n");
}