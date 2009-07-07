#include <iostream>
using namespace std;

class CPoint
{
public:
  CPoint(int x, int y) { xPos = x; yPos = y;}
  CPoint(){};
  int getxPos() { return xPos;}
  int getyPos() { return yPos;}
  void setPos(int x, int y) { xPos = x; yPos = y;}
  void Copy(CPoint cp) { *this = cp;}
  void Print() { cout << "(" << xPos << ", " << yPos << ")";}
private:
  int xPos, yPos;
};

class CRect
{
public:
  CRect(int x1, int y1, int x2, int y2)
  {
    m_ptLT = CPoint(x1, y1);
    m_ptRB = CPoint(x2, y2);
  }
  void print()
  {
    cout << "(" << m_ptLT.getxPos() << "," 
	 << m_ptLT.getyPos() << ")" 
	 << "\t" << "(" << m_ptRB.getxPos() << "," 
	 << m_ptRB.getyPos() << ")" << endl;
  }
private:
  CPoint m_ptLT, m_ptRB;
  static int sss;
};

int CRect::sss = 10;

class Te
{
public:
  Te(int a=0) {}
};

int main(int argc, char **argv)
{
  CPoint c(10,20), c1;
  c.Print();
  c1.Copy(c);
  c1.Print();
  c.setPos(1,2);
  c1.Print();
  cout << endl << sizeof(CPoint) << endl
       << sizeof(c) << endl;
  Te t;

  return 0;
}
