#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <algorithm>
#include <string>
#include <set>

using namespace std::chrono;
using namespace std;

int main()
{
  auto t1 = high_resolution_clock::now();

  string d = "123456789";
  set<int> a;

  do {
    string t1 = d.substr(0, 1);
    string t2 = d.substr(1, 4);
    string t3 = d.substr(0, 2);
    string t4 = d.substr(2, 3);
    string a1 = d.substr(5, 4);
    string a2 = d.substr(5, 4);

    if(stoi(t1) * stoi(t2) == stoi(a1))
      a.insert(stoi(a1));
    if(stoi(t3) * stoi(t4) == stoi(a2))
      a.insert(stoi(a2));

  } while(next_permutation(d.begin(), d.end()));

  int sum = 0;
  for(int s : a)
    sum += s;
  cout << sum << endl;


  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

