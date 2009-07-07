/*文件名:exp3-1.cpp*/
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct 
{
	ElemType elem[MaxSize];
	int top;		/*栈指针*/
} SqStack;
extern void InitStack(SqStack *&s);
extern void ClearStack(SqStack *&s);
extern int StackLength(SqStack *s);
extern int StackEmpty(SqStack *s);
extern int Push(SqStack *&s,ElemType e);
extern int Pop(SqStack *&s,ElemType &e);
extern int GetTop(SqStack *s,ElemType &e);
extern void DispStack(SqStack *s);
void main()
{
	ElemType e;
	SqStack *s;
	printf("(1)初始化栈s\n");
	InitStack(s);
	printf("(2)栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("(3)依次进栈元素a,b,c,d,e\n");
	Push(s,'a');
	Push(s,'b');
	Push(s,'c');
	Push(s,'d');
	Push(s,'e');
	printf("(4)栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("(5)栈长度:%d\n",StackLength(s));
	printf("(6)从栈顶到栈底元素:");DispStack(s);
	printf("(7)出栈序列:");
	while (!StackEmpty(s))
	{
		Pop(s,e);
		printf("%c ",e);
	}
	printf("\n");
	printf("(8)栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("(9)释放栈\n");
	ClearStack(s);
}
