#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  vector<int> ds {1};

  int limit = 100;
  for(int i = 2; i <= limit; ++i) {
    int rest = 0;
    for(int j = 0; j < ds.size(); ++j) {
      int n = ds[j] * i + rest;
      ds[j] = n % 10;
      rest = n / 10;
    }
    while(rest != 0) {
      ds.push_back(rest % 10);
      rest /= 10;
    }
  }

  int sum = 0;
  for(int d : ds)
    sum += d;

  cout << sum << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

