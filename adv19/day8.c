#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

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

  int min0 = 25*6+1;
  int prod = 0;
  int counter[3];
  int image[6][25];
  for(int i = 0; i < 6; ++i)
    for(int j = 0; j < 25; ++j)
      image[i][j] = 2;
  int num;
  while(fscanf(fp, "%1d", &num) > 0) {
    fseek(fp, -1, SEEK_CUR);
    memset(counter, 0, sizeof(counter));
    for(int i = 0; i < 6; ++i) {
      for(int j = 0; j < 25; ++j) {
        fscanf(fp, "%1d", &num);
        ++counter[num];
        if(image[i][j] == 2)
          image[i][j] = num;
      }
    }
    if(min0 > counter[0]) {
      min0 = counter[0];
      prod = counter[1]*counter[2];
    }
  }
  printf("Checksum: %d\n", prod);

  for(int i = 0; i < 6; ++i) {
    for(int j = 0; j < 25; ++j) {
      if(image[i][j] == 1)
        printf("0");
      else
        printf(" ");
    }
    printf("\n");
  }
}
