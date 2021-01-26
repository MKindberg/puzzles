#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>
#include <math.h>
#include <set>

using namespace std::chrono;
using namespace std;

vector<int> primes_below(int max)
{
  int count = 1;
  bool numbers[max];
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
  vector<int> primes;
  primes.reserve(count);
  primes.push_back(2);
  int idx = 2;
  for(int i = 3; i < max; i += 2)
    if(numbers[i])
      primes.push_back(i);
    
  return primes;
}

vector<int> prime_factors(vector<int> primes, int n)
{
  vector<int> factors;
  for(int p : primes) {
    while(n % p == 0) {
      n /= p;
      factors.push_back(p);
    }
    if(n == 1)
      break;
  }
  return factors;
}

set<int> factors_rec(vector<int> p_factors, int n, int i)
{
  if(i == p_factors.size())
    return {1};
  set<int> factors;
  factors.insert(n * p_factors[i]);
  set<int> f1 = factors_rec(p_factors, n, i+1);
  set<int> f2 = factors_rec(p_factors, n*p_factors[i], i+1);
  factors.insert(f1.begin(), f1.end());
  factors.insert(f2.begin(), f2.end());
  return factors;
}
set<int> factors(vector<int> primes, int n)
{
  vector<int> p_factors = prime_factors(primes, n);
  return factors_rec(p_factors, 1, 0);
}


int num_factors(vector<int> primes, int n)
{
  return factors(primes, n).size();
}

int main()
{
  auto t1 = high_resolution_clock::now();

  vector<int> primes = primes_below(10000);

  int n = 1;
  for(int i = 2;; n += i, ++i)
    if(n % 2 == 0 && factors(primes, n).size() > 500)
      break;

  cout << n << endl;


  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

