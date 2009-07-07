#include <iostream>
class String;

istream& operator>>(istream&, String&);
ostream& operator<<(ostream&, String&);

class String
{
  friend istream& operator>>(istream&, String&);
  friend ostream& operator<<(ostream&, String&);
 public:
  String();
  String(const char*);
  String(const String&);

  ~String();

  String& operator=(const String&);
  String& operator=(const char*);

  char& operator[](int) const;

  String& operator+=(const String&);
  String& operator+=(const char*);

  bool operator==(const String&);
  bool operator==(const char*);

  int size() { return _size;}
  char* c_str() { return _string;}

 private:
  int _size;
  char *_string;
};
