#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std::chrono;
using namespace std;

int name_score(string name)
{
  int s = 0;
  for(char n : name){
    s += n - 'A' + 1;
  }
  return s;
}
int main()
{
  auto t1 = high_resolution_clock::now();

  fstream f;
  f.open("22.in", ios::in);
  if(!f) {
    cout << "Failed to open file" << endl;
    return 1;
  }
  vector<string> names;
  names.reserve(5200);

  string name;
  while(getline(f, name, ','))
    names.push_back(name.substr(1, name.length()-2));
  f.close();

  sort(names.begin(), names.end());

  long tot_score = 0;
  for(int i = 0; i < names.size(); ++i)
    tot_score += (i+1) * name_score(names[i]);

  cout << tot_score << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(t2 - t1); 
  cout << endl << duration.count() << " us" << endl;
  return 0;
}

