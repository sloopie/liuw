#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 1024

typedef struct node {
	char		data;
	struct node *lchild;
	struct node *rchild;
} BTNode;

BTNode *stack[MaxSize];
int top;

int isLeaf(BTNode *bt)
{
	return (!bt->lchild && !bt->rchild);
}


void DispBTNode(BTNode *b)
{
	if (b) {
		printf("%c", b->data);
		if (b->lchild || b->rchild) {
			printf("(");
			DispBTNode(b->lchild);
			if (b->rchild)
				printf(",");
			DispBTNode(b->rchild);
			printf(")");
		}
	}
}

void PrintLeaf(BTNode *bt)
{
	if (bt) {
		if (!bt->lchild && !bt->rchild)
			printf("%c ", bt->data);
		PrintLeaf(bt->lchild);
		PrintLeaf(bt->rchild);
	}
}

BTNode *CreateBTNode(char *str)
{
	BTNode *St[MaxSize], *p = NULL, *ret = NULL;
	int top = -1, k, j = 0;
	char ch;
	ret = NULL;
	ch = str[j];
	while (ch != '\0') {
		switch (ch) {
			case '(':
				top++;
				St[top] = p;
				k = 1;
				break;
			case ')':
				top--;
				break;
			case ',':
				k = 2;
				break;
			default:
				p = (BTNode *)malloc(sizeof(BTNode));
				p->data = ch;
				p->lchild = p->rchild = NULL;
				if (!ret) 
					ret = p;
				else {
					switch (k) {
						case 1:
							St[top]->lchild = p;
							break;
						case 2:
							St[top]->rchild = p;
							break;
					}
				}
		}
		j++;
		ch = str[j];
	}
	return ret;
}

void FindPath(BTNode *bt)
{
	struct tnode {
		BTNode *node;
		int parent;
	} qu[MaxSize];
	int front, rear, p;
	
	front = rear = -1;
	rear++;
	qu[rear].node = bt;
	qu[rear].parent = -1;

	while (front < rear) {
		front++;
		bt = qu[front].node;
		if (isLeaf(bt)) {
			printf("path: ");
			p = front;
			while (qu[p].parent != -1) {
				printf("%c ", qu[p].node->data);
				p = qu[p].parent;
			}
			printf("%c\n", qu[p].node->data);
		}
		if (bt->lchild) {
			rear++;
			qu[rear].node = bt->lchild;
			qu[rear].parent = front;
		}
		if (bt->rchild) {
			rear++;
			qu[rear].node = bt->rchild;
			qu[rear].parent = front;
		}
	}
}

void LongPath(BTNode *bt, char path[], int pathlen, 
				char longpath[], int *llen)

{
	int i;
	if (!bt) {
		if (pathlen > *llen) {
			for (i = pathlen - 1; i >= 0; i--)
				longpath[i] = path[i];
			*llen = pathlen;
		}
	}else{
		path[pathlen] = bt->data;
		pathlen++;
		LongPath(bt->lchild, path, pathlen, longpath, llen);
		LongPath(bt->rchild, path, pathlen, longpath, llen);
		pathlen--;
	}
}

int main(int argc, char **argv)
{
	BTNode *bt;
	int height, width, nleaf, nnode;
	int i, llen = 0;
	char path[MaxSize], longpath[MaxSize];
	char exp[] = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";

	bt = CreateBTNode(exp);
	DispBTNode(bt);
	puts("\nLeaves: ");
	PrintLeaf(bt);
	puts("");
	FindPath(bt);
	LongPath(bt, path, 0, longpath, &llen);
	puts("Longest path is:");
	for (i = llen; i >= 0; i--)
		printf("%c ", longpath[i]);
	puts("");
	return 0;
}
