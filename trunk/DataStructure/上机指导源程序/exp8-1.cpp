/*文件名:exp8-1.cpp*/
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
extern GLNode *CreatGL(char *&s);	/*外部函数在algo8-1.cpp中*/
extern int GLLength(GLNode *h);
extern int GLDepth(GLNode *h);
extern void DispGL(GLNode *h);
void main()
{
	GLNode *g;
	char *str="(b,(b,a,a),((a,b),c))";
	g=CreatGL(str);
	printf(" 广义表g:");DispGL(g);printf("\n");
	printf(" 广义表g的长度:%d\n",GLLength(g));
	printf(" 广义表g的深度:%d\n",GLDepth(g));
	printf("\n");
}
