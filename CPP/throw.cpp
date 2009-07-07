#include <iostream>
#include <string>
using namespace std;

void f() throw(string, int);

int main()
{
  try {
    // throw string("Test throw");
    f();
  }catch(string s){
    std::cerr << s << endl;
    // throw;
  }
  return 0;
}


void f() throw(int, string)
{
  throw string("in f()");
  return;
}
