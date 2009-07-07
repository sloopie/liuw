#include "String.h"
#include <cstring>

bool String::
operator==(const String &rhs)
{
  if (_size != rhs._size)
    return false;
  return strcmp(_string, rhs._string) ? false : true;
}

bool String::
operator==(const char *s)
{
  return strcmp(_string, s) ? false : true;
}

String::
String():
  _size(0),
  _string(NULL)
{}

String::
String(const String &rhs)
{
  _size = rhs._size;
  if (!rhs._string)
    _string = NULL;
  else {
    _string = new char[_size+1];
    strcpy(_string, rhs._string);
  }
}

String::
~String()
{
  delete [] _string;
}


String& String::
operator=(const char *s)
{
  if (!s) {
    _size = 0;
    delete [] _string;
    _string = NULL;
  }
  else {
    _size = strlen(s);
    delete [] _string;
    _string = new char[_size+1];
    strcpy(_string, s);
  }
  return *this;
}

String& String::
operator=(const String &rhs)
{
  if (this != &rhs) {
    delete [] _string;
    _size = rhs._size;
    if (!rhs._string)
      _string = NULL;
    else {
      _string = new char[_size+1];
      strcpy(_string, rhs._string);
    }
  }
  return *this;
}

char& String::
operator[](int idx)
{
  assert(idx >= 0 && idx < _size);
  return _string[idx];
}

String& String::
operator+=(const String &rhs)
{
  if (rhs._string) {
    String tmp(*this);

    _size = rhs._size;
    delete [] _string;
    _string = new char[_size+1];
    strcpy(_string, tmp._string);
    strcpy(_string+tmp._size, rhs._string);
  }
  return *this;
}

String& String::
operator+=(const char *s)
{
  if (s) {
    String tmp(*this);

    _size += strlen(s);
    delete [] _string;
    _string = new char[_size+1];

    strcpy(_string, tmp._string);
    strcpy(_string+tmp._size, s);
  }
  return *this;
}




#include <iomanip>
istream&
operator>>(istream *is, String &s)
{
  const int limit_string_size = 4096;
  char inBuf[limit_string_size];

  is >> setw(limit_string_size) >> inBuf;
  s = inBuf;

  return is;
}

ostream&
operator<<(ostream &os, String &s)
{
  return os << s.c_str();
}
