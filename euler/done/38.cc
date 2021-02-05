#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <cmath>
#include <string>
#include <algorithm>

using namespace std::chrono;
using namespace std;

bool is_conc(string s)
{
  for(int i = 2; i < 9; ++i) {
    bool conc = true;
    int n = stoi(s.substr(0, 9/i));
    for(int j = 1; j < i-1; ++j) {
      if(stoi(s.substr(9/i*j, 9/i)) != (j+1)*n) {
        conc = false;
        break;
      }
    }
    if(conc && stoi(s.substr(9/i*(i-1), 9)) != (i)*n)
      conc = false;
    else if(conc)
      return true;
  }
  return false;
}

int main()
{
  auto t1 = high_resolution_clock::now();

  cout << is_conc(string("192384576")) << endl;
  string s("987654321");
  while(!is_conc(s) && prev_permutation(s.begin(), s.end()));
  cout << s << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

