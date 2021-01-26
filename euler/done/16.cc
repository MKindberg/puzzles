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

  int power = 1000;
  for(int p = 0; p < power; p += 2) {
    int rest = 0;
    for(int i = 0; i < ds.size(); ++i) {
      int n = ds[i] * 4 + rest;
      ds[i] = n % 10;
      rest = n / 10;
    }
    if(rest != 0)
      ds.push_back(rest);
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

