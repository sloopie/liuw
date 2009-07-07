/*
 * Consider a function which, for a given whole number n, returns the number
 * of ones required when writing out all number between 0 and n.
 * For example, f(1) = 1, f(13) = 6. Notice that f(1) = 1. What is the next
 * largest n such that f(n) = n? n<=4000000000
 *    e.g. f(13) = 6
 * because the number of "1" in 1,2,3,4,5,6,7,8,9,10,11,12,13 is 6.
 *
 */



#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>
using namespace std;

int f(int n);
int count1(int n);
int cal(unsigned int number, int nwei, int count1, unsigned int ncount);

int gTable[10];
const unsigned int gMAX = 4000000000L;

int main(int argc, char **argv)
{
    int i;
    unsigned int n = 1;
    unsigned int ncount = 0;
    int nwei = 0;
    int ncount1;

    int beginTime = GetTickCount();
    int endTime;

    for (i = 0; i < 10; i++) {
        n *= 10;
        gTable[i] = f(n-1);
    }

    n = 0;
    nwei = 0;
    ncount1 = 0;
    while (n < gMAX) {
        unsigned int temp;

        temp = 1;

        ncount = cal(n, nwei, ncount1, ncount);
        for (i = 0; i < nwei; i++)
            temp *= 10;
        n += temp;

        if ((n / temp) / 10 == 1)
            ++nwei;
        ncount1 = count1(n);
    }

    endTime = GetTickCount();
    endTime -= beginTime;

    printf("times: %d ms\n", endTime);
    return 0;
}

int f(int n)
{
    int ret = 0;
    int ntemp = n;
    int ntemp2 = 1;
    int i = 1;

    while (ntemp) {
        ret += (((ntemp-1)/10)+1) * i;
        if ((ntemp%10) == 1) {
            ret -= i;
            ret += ntemp2;
        }
        ntemp = ntemp/10;
        i *= 10;
        ntemp2 = n%i+1;
    }
    return ret;
}

int count1(int n)
{
    int count = 0;
    while (n) {
        if ((n%10) == 1)
            count++;
        n /= 10;
    }
    return count;
}

int cal(unsigned int number, int nwei, int count1, unsigned int ncount)
{
    int i, n = 1;
    unsigned int maxcount;
    if (nwei == 0) {
        ncount += count1;
        if (number == ncount) {
            printf("f(%d) = %d\n", number, number);
        }
        return ncount;
    }

    for (i = 0; i < nwei; i++)
        n *= 10;
    maxcount = ncount + gTable[nwei-1];
    maxcount += count1*n;
    if (ncount > (number + (n-1)))
        return maxcount;

    if (maxcount < number)
        return maxcount;
    n /= 10;
    for (i = 0; i < 10; i++) {
        if (i == 1)
            ncount = cal(number+i*n, nwei-1,count1+1,ncount);
        else
            ncount = cal(number+i*n, nwei-1, count1, ncount);
    }
    return ncount;
}
