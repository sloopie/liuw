/*�ļ���:exp8-2.cpp*/
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
    struct lnode *link;				/*ָ����һ��Ԫ��*/
} GLNode;
extern GLNode *GLCopy(GLNode *p);	/*�����ⲿ������algo8-2.cpp��*/
extern GLNode *head(GLNode *h);
extern GLNode *tail(GLNode *h);
extern GLNode *CreatGL(char *&s);	/*�����ⲿ������algo8-1.cpp��*/
extern void DispGL(GLNode *h);
void main()
{
	GLNode *g,*gh,*gt;
	char *str1="(a,(a),((a)))";
	char *str2="(((a)))";
	char *str3="(a,(a,b),((a,b),c))";
	g=CreatGL(str1);
	printf("  �����g1:");DispGL(g);printf("\n");
	gh=head(g);
	printf("    g1��ͷ:");DispGL(gh);
	gt=tail(g);
	printf("    g1��β:");DispGL(gt);printf("\n\n");
	g=CreatGL(str2);
	printf("  �����g2:");DispGL(g);printf("\n");
	gh=head(g);
	printf("    g2��ͷ:");DispGL(gh);
	gt=tail(g);
	printf("    g2��β:");DispGL(gt);printf("\n\n");
	g=CreatGL(str3);
	printf("  �����g3:");DispGL(g);printf("\n");
	gh=head(g);
	printf("    g3��ͷ:");DispGL(gh);
	gt=tail(g);
	printf("    g3��β:");DispGL(gt);printf("\n\n");
}
