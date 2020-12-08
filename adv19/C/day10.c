#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

FILE* openFile(int argc, const char* argv[])
{
  char filename[50];
  if(argc < 2) {
    printf("Which file do you want to read from? ");
    scanf("%s", filename);
  } else {
    strncpy(filename, argv[1], 50);
  }
  FILE* fp = fopen(filename, "r");
  if(fp == NULL) {
    fprintf(stderr, "Couldn't open file %s: %s", argv[1], strerror(errno));
    exit(1);
  }
  return fp;
}

void getSize(FILE* fp, int* width, int* height)
{
  char c = 0;
  while(fscanf(fp, "%c", &c) > 0 && c != '\n')
    ++(*width);
  char dummy[(*width)+1];
  ++(*height);
  while(fscanf(fp, "%s", dummy) > 0)
    ++(*height);

  rewind(fp);

}
int** getMap(FILE* fp, int width, int height)
{
  int i = 0, j = 0;
  char c = 0;
  int (*map)[width] = malloc(width*height*sizeof(int));
  while(fscanf(fp, "%c", &c) > 0) {
    switch(c) {
      case '\n':
        i = -1;
        ++j;
        break;
      case '.':
        map[j][i] = 0;
        break;
      case '#':
        map[j][i] = 1;
        break;
      default:
        fprintf(stderr, "Invalid map");
        fclose(fp);
        exit(1);
    }
    ++i;
  }
  return map;
}
int main(int argc, const char* argv[])
{
  FILE* fp = openFile(argc, argv);
  int width = 0, height = 0;
  getSize(fp, &width, &height);
  int** map = getMap(fp, width, height);

  fclose(fp);
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      printf("%d", map[i][j]);
    }
    printf("\n");
  }

  free(map);
}
