#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 4096

typedef struct node {
    char data;
    struct node *lchild;
    struct node *rchild;
} BTNode;

void trans(char *exp, char postexp[])
{
    struct {
        char data[MaxSize];
        int top;
    } op;
    int i = 0;
    op.top = -1;
    while (*exp != '\0') {
        switch (*exp) {
            case '+':
            case '-':
                while (op.top != -1) {
                    postexp[i++] = op.data[op.top];
                    op.top--;
                }
                op.top++;
                op.data[op.top] = *exp;
                exp++;
                break;
            case '*':
            case '/':
                while (op.data[op.top] == '*' || op.data[op.top] == '/') {
                    postexp[i++] = op.data[op.top];
                    op.top--;
                }
                op.top++;
                op.data[op.top] = *exp;
                exp++;
                break;
            case ' ':
                break;
            default:
                while (*exp >= 'a' && *exp <= 'z') {
                    postexp[i++] = *exp;
                    exp++;
                }
        }
    }
    while (op.top != -1) {
        postexp[i++] = op.data[op.top];
        op.top--;
    }
    postexp[i] = '\0';
}

void midorder(BTNode *bt)
{
    if (bt != NULL) {
        midorder(bt->lchild);
        printf("%c", bt->data);
        midorder(bt->rchild);
    }
    return;
}

void DispBTNode(BTNode *b)
{
    if (b != NULL) {
        printf("%c", b->data);
        if (b->lchild != NULL || b->rchild != NULL) {
            printf("(");
                    DispBTNode(b->lchild);
                    if (b->rchild != NULL) printf(",");
                    DispBTNode(b->rchild);
                    printf(")");
        }
    }
}


BTNode *CreateBT2(char *postexp, char *midexp, int n)
{
    BTNode *s;
    char r, *p;
    int k;
    if (n <= 0)
        return NULL;
    r = *(postexp + n - 1);
    s = (BTNode *)malloc(sizeof(BTNode));
    s->data = r;
    for (p = midexp; p < midexp + n; p++)
        if (*p == r)
            break;
    k = p - midexp;
    s->lchild = CreateBT2(postexp, midexp, k);
    s->rchild = CreateBT2(postexp+k, p+1, n-k-1);
    return s;
}

int main(int argc, char **argv)
{
    char midexp[] = "a+b*c-e/f";
    char postexp[50];
    BTNode *bt;
    trans(midexp, postexp);
    printf("%d %d\n", strlen(midexp), strlen(postexp));
    printf("%s %s\n", midexp, postexp);
    bt = CreateBT2(postexp, midexp, strlen(midexp));
    DispBTNode(bt);
    puts("");
    midorder(bt);
    puts("");
    return 0;
}
