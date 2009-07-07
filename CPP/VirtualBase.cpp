#include <iostream>
using namespace std;

class A
{
	public:
		int x;
		A(int a=0) { x = a;}
};

class B1: virtual public A
{
	public:
		int y1;
		B1(int a=0, int b=0)
			:A(b)
		{
			y1 = a;
		}
		void print(void)
		{
			cout << "B1:x = " << x << ", y1 = " << y1 << endl;
		}
};

class B2: virtual A
{
	public:
		int y2;
		B2(int a=0, int b=0)
			:A(b)
		{
			y2 = a;
		}
		void print(void)
		{
			cout << "B2:x = " << x << ", y2 = " << y2 << endl;
		}
};

class C: public B1, public B2
{
	public:
		int z;
		C(int a, int b, int d, int e, int m)
			:B1(a,b), B2(d,e)
		{
			z = m;
		}
		void print()
		{
			B1::print();
			B2::print();
			cout << "z = " << z << endl;
		}
};

int main()
{
	C c1(100, 200, 300, 400, 500);
	c1.print();
	c1.x = 400;
	c1.print();
	return 0;
}
