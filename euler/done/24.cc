#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>
#include <algorithm>

using namespace std::chrono;
using namespace std;

int fac(int n) {
  int p = 1;
  for(int i = 1; i <= n; ++i)
    p *= i;
  return p;
}
void swap(vector<int>& v, int i, int j)
{
  v[i] ^= v[j];
  v[j] ^= v[i];
  v[i] ^= v[j];
}
int main()
{
  auto t1 = high_resolution_clock::now();

  int permutations = 1000000-1;
  vector<int> v {0,1,2,3,4,5,6,7,8,9};

  for(int i = 0; i < v.size()-1; ++i) {
    sort(v.begin() + i, v.end());
    swap(v, i, permutations/fac(v.size() - 1 - i) + i);
    permutations %= fac(v.size() - 1 - i);
  }
  for(int i : v)
    cout << i;
  cout << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

