#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std::chrono;
using namespace std;

vector<bool> is_prime_list(int max)
{
  int count = 1;
  vector<bool> numbers(max, true);
  for(int i = 4; i < max; i += 2)
    numbers[i] = false;
  numbers[0] = false;
  numbers[1] = false;
  for(int i = 3; i < sqrt(max); i += 2) {
    if(numbers[i]){
      count += 1;
      for(int j = i*i; j < max; j += i){
        numbers[j] = false;
      }
    }
  }
  return numbers;
}
int main()
{
  auto t1 = high_resolution_clock::now();

  int max = 1;
  int ab = 0;
  vector<bool> is_prime = is_prime_list(2000);
  for(int b = 2; b < 1000; ++b)
    // n*n + a*n + b > 0
    // a < n + b/n
    for(int a = -(max+b/max); a < 1000; ++a) {
      int n = 0;
      while(n*n + a*n + b > 0 && is_prime[n*n + a*n + b])
        ++n;
      if(max < n) {
        max = n;
        ab = a*b;
      }
    }

  cout << ab << endl;


  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

