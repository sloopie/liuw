#include <iostream>
using namespace std;

const int N = 5;
const int COLOR = 3;


char c[N+1];
bool flag;
// col 0 and line 0 are never used
char adjvec[N+1][N+1] = {
    { 0, 0, 0, 0, 0, 0},
    { 0, 0, 1, 1, 0, 0},
    { 0, 1, 0, 0, 1, 1},
    { 0, 1, 0, 0, 1, 1},
    { 0, 0, 1, 1, 0, 1},
    { 0, 0, 1, 1, 1, 0}
};

bool isvalid(int k)
{
    for (int i = 1; i <= k; ++i)
        if (adjvec[k][i] == 1 && c[k] == c[i])
            return false;
    return true;
}

void printresult()
{
    for (int i = 1; i <= N; ++i)
        printf("%c ", c[i]+'0');
    puts("");
}

// valid ans: 1 2 2 1 3
void graphcolorrec(int k)
{
    for (int color = 1; color <= COLOR; ++color) {
        c[k] = color;
        if (k < N && isvalid(k))
            graphcolorrec(k+1);
        if (k == N && isvalid(k)) {
            printresult();
        }
    }
}

void graphcoloriter()
{
    bool flag = false;
    int k = 1;
    while (k >= 1) {
        while (c[k] <= 2) {
            c[k] = c[k] + 1;
            if (k == N && isvalid(k))
                printresult();
            else if (k < N && isvalid(k))
                k++;
        }
        c[k] = 0;
        k--;
    }
}

/*
int main()
{
    int k;
    for (k = 1; k <= N; ++k)
        c[k] = 0;

    graphcolorrec(1);
    puts("");
    for (k = 1; k <= N; ++k)
        c[k] = 0;
    graphcoloriter();

    return 0;
}
*/
