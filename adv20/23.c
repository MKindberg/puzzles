#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extract3(int* cups, int* extracted, int current)
{
  int n = current;
  for(int i = 0; i < 3; ++i) {
    n = cups[n];
    extracted[i] = n;
  }
  cups[current] = cups[n];
}

void insert3(int* cups, int dest, int* picked)
{
  int n = cups[dest];
  cups[dest] = picked[0];
  cups[picked[2]] = n;
}

void play(int* cups, int rounds, int maxC, int start)
{
  int current = start;
  int picked[3];
  int dest = 0;

  for(int i = 0; i < rounds; ++i)
  {
    extract3(cups, picked, current);
    if(current > 1)
      dest = current-1;
    else
      dest = maxC;
    while(dest == picked[0] || dest == picked[1] || dest == picked[2])
      if(--dest == 0)
        dest = maxC;
    insert3(cups, dest, picked);
    current = cups[current];

  }
}

int main()
{
  char* data = "364289715";
  int d_len = strlen(data);

  int* cups = malloc(sizeof(int)*1000001);
  for(int i = 0; i < 1000000; ++i)
    cups[i] = i+1;
  for(int i = 0; i < d_len-1; ++i)
    cups[data[i]-48] = data[i+1]-48;
  cups[1000000] = data[0]-48;
  cups[data[d_len-1]-48] = 10;

  play(cups, 10000000, 1000000, data[0]-48);
  printf("%ld\n", (long)cups[1]*cups[cups[1]]);
}
