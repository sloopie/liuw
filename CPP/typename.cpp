#include <iostream>

using namespace std;

template<class T, int size=1024>
class C
{
public:
  void printsize() { 
    cout << size << endl;
    cout << sizeof(buf) << endl;
}
private:
  char buf[size];
};

int main()
{
  C<int> c;
  c.printsize();
  return 0;
}
