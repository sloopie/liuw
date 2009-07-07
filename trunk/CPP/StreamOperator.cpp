#include <iostream>
using namespace std;

class CStudent
{
public:
  friend ostream& operator<<(ostream& os, CStudent &s);
  friend istream& operator>>(istream& is, CStudent &s);
private:
  char strName[10];
  char strID[10];
};

ostream& operator<<(ostream& os, CStudent &s)
{
  os << endl << "Information: " << endl;
  os << "Name: " << s.strName << endl;
  os << "ID: " << s.strID << endl;
  return os;
}

istream& operator>>(istream& is, CStudent &s)
{
  cout << "Please input: " << endl;
  cout << "Name: ";
  is >> s.strName;
  cout << "ID: ";
  is >> s.strID;
  return is;
}

int main()
{
  CStudent one;
  cin >> one;
  cout << one;
  return 0;
}
