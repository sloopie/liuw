/*文件名:exp8-2.cpp*/
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
    struct lnode *link;				/*指向下一个元素*/
} GLNode;
extern GLNode *GLCopy(GLNode *p);	/*以下外部函数在algo8-2.cpp中*/
extern GLNode *head(GLNode *h);
extern GLNode *tail(GLNode *h);
extern GLNode *CreatGL(char *&s);	/*以下外部函数在algo8-1.cpp中*/
extern void DispGL(GLNode *h);
void main()
{
	GLNode *g,*gh,*gt;
	char *str1="(a,(a),((a)))";
	char *str2="(((a)))";
	char *str3="(a,(a,b),((a,b),c))";
	g=CreatGL(str1);
	printf("  广义表g1:");DispGL(g);printf("\n");
	gh=head(g);
	printf("    g1表头:");DispGL(gh);
	gt=tail(g);
	printf("    g1表尾:");DispGL(gt);printf("\n\n");
	g=CreatGL(str2);
	printf("  广义表g2:");DispGL(g);printf("\n");
	gh=head(g);
	printf("    g2表头:");DispGL(gh);
	gt=tail(g);
	printf("    g2表尾:");DispGL(gt);printf("\n\n");
	g=CreatGL(str3);
	printf("  广义表g3:");DispGL(g);printf("\n");
	gh=head(g);
	printf("    g3表头:");DispGL(gh);
	gt=tail(g);
	printf("    g3表尾:");DispGL(gt);printf("\n\n");
}
