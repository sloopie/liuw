#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 1024

typedef struct node {
	char		data;
	struct node *lchild;
	struct node *rchild;
} BTNode;


int
BTNodeHeight(BTNode *b)
{
	int lchildh, rchildh;
	if (!b)
		return 0;
	else {
		lchildh = BTNodeHeight(b->lchild);
		rchildh = BTNodeHeight(b->rchild);
		return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}

void
DispBTNode(BTNode *b)
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

void
FindNode(BTNode *bt, char data)
{
	if (bt) {
		if (bt->data == data)
			printf("%c %c\n", bt->lchild->data, bt->rchild->data);
		FindNode(bt->lchild, data);
		FindNode(bt->rchild, data);
	}
}

int 
CountBTNode(BTNode *b)
{
	static int numNode = 0;
	if (b) {
		numNode++;
		CountBTNode(b->lchild);
		CountBTNode(b->rchild);
	}
	return numNode;
}

int
CountLeaf(BTNode *b)
{
	static int numLeaf = 0;
	if (b) {
		if (!b->lchild && !b->rchild)
			numLeaf++;
		CountLeaf(b->lchild);
		CountLeaf(b->rchild);
	}
	return numLeaf;
}

BTNode *
CreateBTNode(char *str)
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

int
CountWidth(BTNode *bt)
{
	static int n[10];
	static int i = 1;
	static int max = 0;
	if (bt) {
		if (i == 1) {
			n[i]++;
			i++;
			if (bt->lchild)
				n[i]++;
			if (bt->rchild)
				n[i]++;
		}else{
			i++;
			if (bt->lchild)
				n[i]++;
			if (bt->rchild)
				n[i]++;
		}
		if (max < n[i]) max = n[i];
		CountWidth(bt->lchild);
		i--;
		CountWidth(bt->rchild);
	}
	return max;
}

int
main(int argc, char **argv)
{
	BTNode *bt;
	int height, width, nleaf, nnode;
	char exp[] = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";

	bt = CreateBTNode(exp);
	DispBTNode(bt);
	puts("");
	nnode = CountBTNode(bt);
	nleaf = CountLeaf(bt);
	printf("%d %d\n", nnode, nleaf);
	FindNode(bt, 'H');
	height = BTNodeHeight(bt);
	width = CountWidth(bt);
	printf("%d %d\n", height, width-1);
	return 0;
}
