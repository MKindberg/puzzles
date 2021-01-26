#!/bin/bash
tail +3 $0 | g++ -x c++ - && exec ./a.out

#include <iostream>
#include <string>

using namespace std;

bool is_palindrome(int n)
{
  string str = to_string(n);
  int l = str.length();
  for(int i = 0; i < l/2; ++i)
    if(str[i] != str[l-1-i])
      return false;
  return true;
}
int main()
{
  int max = 0;
  for(int i = 999; i > 0; --i)
    for(int j = i; i*j > max; --j)
      if(is_palindrome(i*j)){
        max = i*j;
        break;
      }

  cout << max << endl;

  return 0;
}

