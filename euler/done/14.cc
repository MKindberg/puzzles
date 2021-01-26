#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>

using namespace std::chrono;
using namespace std;

int chainLen(vector<long>& chains, long n)
{
  vector<long> v {n};
  int l = 0;

  while(n != 1) {
    n = n % 2 == 0 ? n/2 : 3 * n + 1;
    if(n < chains.size() && chains[n] != 0) {
      l = chains[n];
      break;
    }
    v.push_back(n);
  }
  for(int i = 1; i <= v.size(); ++i) {
    if(v[v.size() - i] < chains.size())
      chains[v[v.size() - i]] = i + l;
  }

  return v.size() + l;
}
int main()
{
  auto t1 = high_resolution_clock::now();

  int limit = 1000000;
  vector<long> chains(limit, 0);
  int max = 0;
  int maxN = 0;
  for(int i = 1; i < limit; ++i) {
    int l = chainLen(chains, i);
    if(max < l) {
      max = l;
      maxN = i;
    }
  }
  cout << maxN << ": " << max << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

