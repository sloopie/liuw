/*文件名:exp3-2.cpp*/
#include <stdio.h>
#include <malloc.h>
typedef char ElemType;
typedef struct linknode
{
	ElemType data;				/*数据域*/
	struct linknode *next;		/*指针域*/
} LiStack;
extern void InitStack(LiStack *&s);
extern void ClearStack(LiStack *&s);
extern int StackLength(LiStack *s);
extern int StackEmpty(LiStack *s);
extern void Push(LiStack *&s,ElemType e);
extern int Pop(LiStack *&s,ElemType &e);
extern int GetTop(LiStack *s,ElemType &e);
extern void DispStack(LiStack *s);
void main()
{
	ElemType e;
	LiStack *s;
	printf("(1)初始化链栈s\n");
	InitStack(s);
	printf("(2)链栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("(3)依次进链栈元素a,b,c,d,e\n");
	Push(s,'a');
	Push(s,'b');
	Push(s,'c');
	Push(s,'d');
	Push(s,'e');
	printf("(4)链栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("(5)链栈长度:%d\n",StackLength(s));
	printf("(6)从链栈顶到链栈底元素:");DispStack(s);
	printf("(7)出链栈序列:");
	while (!StackEmpty(s))
	{	Pop(s,e);
		printf("%c ",e);
	}
	printf("\n");
	printf("(8)链栈为%s\n",(StackEmpty(s)?"空":"非空"));
	printf("(9)释放链栈\n");
	ClearStack(s);
}
