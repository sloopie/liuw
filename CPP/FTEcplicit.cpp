#include <iostream>
using namespace std;
template<typename T1, typename T2, int ZZZ>
T1 sum(T1 x, T2 y)
{
  return x+y+ZZZ;
}

class CName
{
  char *name;
public:
  CName(char *str=NULL)
  {
    if (str) {
      name = new char[strlen(str)+1];
      strcpy(name, str);
    }
  }
  ~CName()
  {
    if (name) {
      delete [] name;
      name = NULL;
    }
  }

  void SetName(char *str)
  {
    if (name) {
      delete [] name;
      name = NULL;
    }
    if (str) {
      name = new char[strlen(str)+1];
      strcpy(name, str);
    }
  }

  char *GetName()
  {
    return name;
  }
};

template<class T>
void myswap(T *a, T *b)
{
  T temp;
  temp = *a; *a = *b; *b = temp;
}

template<>
void myswap<CName>(CName *a, CName *b)
{
  char *temp = new char[strlen(a->GetName())+1];
  strcpy(temp, a->GetName());
  a->SetName(b->GetName());
  b->SetName(temp);
  delete [] temp;
}

int main()
{
  cout << sum<int, char, 3>(2, 'a') << endl;
  cout << sum<double, double, 5>(2, 5.5) << endl;
  CName one("DING");
  CName two("ZHANGAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
  myswap<CName>(&one, &two);
  cout << one.GetName() << endl;
  cout << two.GetName() << endl;
  return 0;
}
