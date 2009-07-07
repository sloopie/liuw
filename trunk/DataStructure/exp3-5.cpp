#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define W 1
#define _DEBUG_

enum { 
    MaxSize = 4096,
    M       = 5,
    N       = 5
};

int mg[M+1][N+1] = {
    { W, W, W, W, W, W},
    { W, 0, 0, 0, W, W},
    { W, 0, W, 0, 0, W},
    { W, 0, 0, 0, W, W},
    { W, W, 0, 0, 0, W},
    { W, W, W, W, W, W}
};

typedef struct {
    int i;
    int j;
    int pre;
} coord;

coord Qu[MaxSize];
int front = -1;
int rear = -1;

int     mgpath      (int, int, int, int);
void    print       (int);
int     isInQueue   (coord, int, int);

int main (int argc, char **argv) {
    int i;
    mgpath (1, 1, M-1, N-1);
    printf ("Here are the results:\n");
    for (i = 0; i < MaxSize; i++) 
        if (Qu[i].i == M-1 && Qu[i].j == N-1){
            print (i);
            puts ("");
        }
    return 0;
}

int mgpath (int xi, int yi, int xe, int ye) {
    int i, j, find = 0, di;
    rear++;
    Qu[rear].i = xi;
    Qu[rear].j = yi;
    Qu[rear].pre = -1;
    mg[xi][yi] = -1;
#ifdef _DEBUG_
    printf ("0\t(%d, %d, %d)\n", xi, yi, mg[xi][yi]);
#endif

    while (front <= rear) {
        front++;
        i = Qu[front].i;
        j = Qu[front].j;
        for (di = 0; di < 4; di++) {
            switch (di) {
                case 0:
                    i = Qu[front].i-1; j = Qu[front].j; break;
                case 1:
                    i = Qu[front].i; j = Qu[front].j+1; break;
                case 2:
                    i = Qu[front].i+1; j = Qu[front].j; break;
                case 3:
                    i = Qu[front].i; j = Qu[front].j-1; break;
            }
            if (mg[i][j] != W && !isInQueue (Qu[front], i, j) &&
                    i >= 0 && j >= 0) {
                rear++;
                Qu[rear].i = i;
                Qu[rear].j = j;
                Qu[rear].pre = front;
#ifdef _DEBUG_
                printf ("%d\t(%d, %d, %d)\n", rear, i, j, Qu[rear].pre);
#endif
            }
        }
    }
    return 0;
}

void print (int front) {
    int k = front;
    if (k != -1) {
        print (Qu[k].pre);
        printf ("(%d, %d) ", Qu[k].i, Qu[k].j);
    } 
}

int isInQueue (coord c, int i, int j) {
    int t = c.pre;
    while (t != -1) {
        if (Qu[t].i == i && Qu[t].j == j)
            return 1;
        t = Qu[t].pre;
    }
    return 0;
}
