

#include <algorithm>
#include <cstdio>
using namespace std;

const unsigned P = 2013265921; //15*2^27+1
const unsigned OMEGA = 440564289; //root£¬31^15 % P
const unsigned INV_TWO = 1006632961; //2^(-1)
char str[10001];
unsigned a[8192], b[8192], roots[8192];

unsigned Power(unsigned x, unsigned y)
{
   unsigned res = 1;
   for (; y; y /= 2)
   {
        if (y&1) res = (unsigned __int64)res*x%P;
        x = (unsigned __int64)x*x%P;
   }
   return res;
}

void FFT(unsigned x[], int n)
{
    int    i,j,k;
   unsigned root = Power(OMEGA, (1<<27)/n);
   roots[0] = 1;
   for (i = 1; i < n; ++i)
        roots[i] = (unsigned __int64)roots[i-1]*root%P;
   for (i = 0; i < n; ++i)
   {
        j = 0;
        for (int t = i, k = n; k /= 2; t /= 2)
            j = j*2+t%2;
        if (j > i) swap(x[i], x[j]);
   }
   for (k = 2; k <= n; k *= 2)
        for (i = 0; i < n; i += k)
            for (j = 0; j < k/2; ++j)
            {
                unsigned t = (unsigned __int64)roots[n*j/k]*x[i+j+k/2]%P;
                x[i+j+k/2] = (x[i+j]-t+P)%P;
                x[i+j] = (x[i+j]+t)%P;
            };
}

void IFFT(unsigned x[], int n)
{
    int i,j,k;
   unsigned root = Power(OMEGA, (1<<27)/n*(n-1));
   roots[0] = 1;
   for (i = 1; i < n; ++i)
        roots[i] = (unsigned __int64)roots[i-1]*root%P;
   for (i = 0; i < n; ++i)
   {
        j = 0;
        for (int t = i, k = n; k /= 2; t /= 2)
            j = j*2+t%2;
        if (j > i) swap(x[i], x[j]);
   }
   for (k = 2; k <= n; k *= 2)
        for (i = 0; i < n; i += k)
            for (j = 0; j < k/2; ++j)
            {
                unsigned t = (unsigned __int64)roots[n*j/k]*x[i+j+k/2]%P;
                x[i+j+k/2] = (x[i+j]-t+P)%P;
                x[i+j] = (x[i+j]+t)%P;
            };
   unsigned inv_n = 1;
   for (i = n; i /= 2; )
        inv_n = (unsigned __int64)inv_n*INV_TWO%P;
   for (i = 0; i < n; ++i)
        x[i] = (unsigned __int64)x[i]*inv_n%P;
}

int main()
{
   int a_size = 0, b_size = 0, n;
    int size,i;
   gets(str);
   for (size = (int)strlen(str); size > 3; str[size -= 3] = '\0')
        a[a_size++] = atoi(str+size-3);
   a[a_size++] = atoi(str);
   gets(str);
   for (size = (int)strlen(str); size > 3; str[size -= 3] = '\0')
        b[b_size++] = atoi(str+size-3);
   b[b_size++] = atoi(str);

   a_size += b_size;
   for (n = a_size; n != (n&-n); n += n&-n);
   FFT(a, n);
   FFT(b, n);
   for (i = 0; i < n; ++i)
        a[i] = (unsigned __int64)a[i]*b[i]%P;
   IFFT(a, n);

   for (i = 0; i < a_size-1; ++i)
   {
        a[i+1] += a[i]/1000;
        a[i] %= 1000;
   }
   if (!a[a_size-1]) --a_size;
   printf("%u", a[a_size-1]);
   for (i = a_size-2; i >= 0; --i)
        printf("%03u", a[i]);
   putchar('\n');
   return 0;
}

