/*文件名:exp3-3.cpp*/
#include <stdio.h>
#include <malloc.h>
#define MaxSize 5
typedef char ElemType;
typedef struct 
{
	ElemType elem[MaxSize];
	int front,rear;		/*队首和队尾指针*/
} SqQueue;
extern void InitQueue(SqQueue *&q);
extern void ClearQueue(SqQueue *&q);
extern int QueueLength(SqQueue *q);
extern QueueEmpty(SqQueue *q);
extern int enQueue(SqQueue *&q,ElemType e);
extern int deQueue(SqQueue *&q,ElemType &e);
void main()
{
	ElemType e;
	SqQueue *q;
	printf("(1)初始化队列q\n");
	InitQueue(q);
	printf("(2)依次进队列元素a,b,c\n");
	if (enQueue(q,'a')==0) printf("队满,不能进队\n");
	if (enQueue(q,'b')==0) printf("队满,不能进队\n");
	if (enQueue(q,'c')==0) printf("队满,不能进队\n");
	printf("(3)队列为%s\n",(QueueEmpty(q)?"空":"非空"));
	if (deQueue(q,e)==0) 
		printf("队空,不能出队\n");
	else
		printf("(4)出队一个元素%c\n",e);
	printf("(5)队列q的元素个数:%d\n",QueueLength(q));
	printf("(6)依次进队列元素d,e,f\n");
	if (enQueue(q,'d')==0) printf("队满,不能进队\n");
	if (enQueue(q,'e')==0) printf("队满,不能进队\n");
	if (enQueue(q,'f')==0) printf("队满,不能进队\n");
	printf("(7)队列q的元素个数:%d\n",QueueLength(q));
	printf("(8)出队列序列:");
	while (!QueueEmpty(q))
	{	deQueue(q,e);
		printf("%c ",e);
	}
	printf("\n");
	printf("(9)释放队列\n");
	ClearQueue(q);
}
