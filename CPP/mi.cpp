#include <iostream>
using namespace std;

class A
{
public:
  int a;
};

class B: public A
{
public:
  int b;
};

class C: public B, public A
{
public:
  C(int c=0) { this->c = c;}
  int c;
};
