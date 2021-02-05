#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>
#include <cmath>

using namespace std::chrono;
using namespace std;

vector<bool> primes_below(int max)
{
  int count = 1;
  vector<bool> numbers(max, false);
  for(int i = 0; i < max; ++i)
    numbers[i] = i%2 == 1;
  numbers[1] = false;
  numbers[2] = true;
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

  int limit = 1000000;
  vector<bool> is_prime = primes_below(limit);
  int count = 0;
  for(int n = 1; n < limit; ++n) {
    int nn = n;
    bool circular = true;
    int l = log10(n);

    for(int i = 0; i < l+1; ++i) {
      nn = nn/10 + (nn%10)*pow(10, l);
      if(!is_prime[nn]) {
        circular = false;
        break;
      }
    }
    if(circular)
      ++count;
  }
  cout << count << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

