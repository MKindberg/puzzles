#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct Point{
  short x;
  short y;
  int steps;
} Point;

int dist(Point p)
{
  return abs(p.x) + abs(p.y);
}

int compPoint(const void* e1, const void* e2)
{
  Point p1 = *(Point*)e1;
  Point p2 = *(Point*)e2;

  return dist(p1)-dist(p2);
}

int readWire(FILE* fp, Point* wire)
{
  Point p = (Point){0, 0, 0};
  char dir;
  int steps;
  while(fscanf(fp, "%c%d,", &dir, &steps) == 2) {
    for(int i = 0; i < steps; ++i) {
      p.steps++;
      if(wire != NULL){
        switch(dir){
          case 'U':
            p.y++;
            break;
          case 'D':
            p.y--;
            break;
          case 'R':
            p.x++;
            break;
          case 'L':
            p.x--;
            break;
        }
        wire[p.steps-1] = p;
      }
    }
  }
  return p.steps;
}

int main(int argc, const char* argv[])
{
  if(argc < 2) {
    fprintf(stderr, "Please supply a file with input\n");
    return 1;
  }
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL) {
    fprintf(stderr, "Couldn't open file %s: %s", argv[1], strerror(errno));
    return 1;
  }

  int c1 = readWire(fp, NULL);
  int c2 = readWire(fp, NULL);
  rewind(fp);
  Point* wire1 = malloc(c1*sizeof(Point));
  readWire(fp, wire1);
  Point* wire2 = malloc(c2*sizeof(Point));
  readWire(fp, wire2);

  qsort(wire1, c1, sizeof(Point), compPoint);
  qsort(wire2, c2, sizeof(Point), compPoint);

  int x, y;
  int jj = 0;
  int minSteps = c1+c2;
  int closest = -1;
  for(int i = 0; i < c1; ++i) {
    Point p1 = wire1[i];
    if(p1.steps > minSteps)
      continue;
    for(int j = jj; j < c2; ++j) {
      Point p2 = wire2[j];
      if(p1.x == p2.x && p1.y == p2.y)
      {
        if(closest == -1)
          closest = dist(p1);
        if(p1.steps + p2.steps < minSteps)
          minSteps = p1.steps + p2.steps;
        break;
      } else if(dist(p2) > dist(p1)) {
        // No need to check point longer away than p1
        break;
      } else if(dist(p2) < dist(p1)) {
        // No need to check smaller points again since both list are sorted on distance
        jj = j+1;
      }
    }
  }

  printf("Closest crossing: %d\n", closest);
  printf("Minimum total steps to first intersection: %d\n", minSteps);
}
