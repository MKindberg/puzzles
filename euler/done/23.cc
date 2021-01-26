#!/bin/bash
tail +3 $0 | g++ -std=c++17 -O3 -x c++ - && exec ./a.out

#include <iostream>
#include <chrono> 
#include <vector>
#include <set>
#include <math.h>

using namespace std::chrono;
using namespace std;

vector<int> primes;

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

vector<int> prime_factors(int n)
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
set<int> factors(int n)
{
  vector<int> p_factors = prime_factors(n);
  return factors_rec(p_factors, 1, 0);
}

bool is_abundant(int n)
{
  int sum = -n;
  for(int f : factors(n)) {
    sum += f;
    if(sum > n)
      return true;
  }
  return false;
}
vector<int> abundant_below(int n)
{
  vector<int> abundant;
  for(int i = 1; i < n; ++i)
    if(is_abundant(i))
      abundant.push_back(i);

  return abundant;
}

int main()
{
  auto t1 = high_resolution_clock::now();

  int limit = 28123;
  primes = primes_below(limit/2);

  vector<int> abundant = abundant_below(limit);

  vector<bool> sum_pair(2*limit, false);
  for(int i = 0; i < abundant.size(); ++i)
    for(int j = i; j < abundant.size() && abundant[i] + abundant[j] < sum_pair.size(); ++j)
      sum_pair[abundant[i]+abundant[j]] = true;

  long sum = 0;
  for(int i = 1; i < limit; ++i)
    if(!sum_pair[i])
      sum += i;

  cout << sum << endl;

  auto t2 = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(t2 - t1); 
  cout << endl << duration.count() << " ms" << endl;
  return 0;
}

