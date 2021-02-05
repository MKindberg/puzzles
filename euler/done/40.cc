#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <cmath>

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  int digits[7]; // the 10^i:th digit
  int digit_len[7]; // number of digits in all (i+1) digit numbers
  for(int i = 0; i < 7; ++i) {
    digit_len[i] = pow(10, i) * 9 * (i+1);
  }

  for(int i = 0; i < 7; ++i) {
    int p = pow(10, i);
    int l;
    int n = 0;
    for(l = 0; l < 7; ++l)
      if(p > digit_len[l]) {
        p -= digit_len[l];
        n += pow(10, l) * 9;
      }
      else
        break;
    // we want the p/(l+1) (l+1) digit number
    n += p/(l+1.0) + 0.5; // The digit we want is in the number n
    int d = (p/(l+1.0) - floor(p/(l+1.0))) * (int)log10(n); // we want digit d from n
    digits[i] = (int)(n / pow(10, (int)log10(n) - d)) % 10;
  }

  int prod = 1;
  for(int d : digits)
    prod *= d;

  cout << prod << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

