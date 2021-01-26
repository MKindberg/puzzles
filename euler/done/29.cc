#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <set>
#include <utility>
#include <cmath>

using namespace std::chrono;
using namespace std;

pair<int, int> reduce(int a, int b)
{
  return {a, b};
}
int main()
{
  auto t1 = high_resolution_clock::now();

  int u = 0;
  int a0 = 2, b0 = 2, a1 = 100, b1 = 100;

  set<pair<int, int>> unique;

  // Start out with all combinations
  int all[a1+1][b1+1];
  for(int i = a0; i <= a1; ++i){
    all[i][0] = i;
    for(int j = b0; j <= b1; ++j)
      all[i][j] = j;
  }

  // Reduce the combinations that can be reduced
  for(int a = a0; a <= a1; ++a) {
    for(int n = 2; pow(a, n) <= a1; ++n){
      int p = pow(a, n);
      if(all[p][0] == p) {
        all[p][0] = a;
        for(int b = b0; b <= b1; ++b){
          all[p][b] *= n;
        }
      }
    }
  }

  // Filter out the unique ones
  for(int i = a0; i <= a1; ++i)
    for(int j = b0; j <= b1; ++j)
      unique.insert({all[i][0], all[i][j]});

  cout << unique.size() << endl;


  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

