/*�ļ���:exp8-1.cpp*/
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
extern GLNode *CreatGL(char *&s);	/*�ⲿ������algo8-1.cpp��*/
extern int GLLength(GLNode *h);
extern int GLDepth(GLNode *h);
extern void DispGL(GLNode *h);
void main()
{
	GLNode *g;
	char *str="(b,(b,a,a),((a,b),c))";
	g=CreatGL(str);
	printf(" �����g:");DispGL(g);printf("\n");
	printf(" �����g�ĳ���:%d\n",GLLength(g));
	printf(" �����g�����:%d\n",GLDepth(g));
	printf("\n");
}
