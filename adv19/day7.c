#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

void swap(int* array, int i, int j)
{
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

int permutations(int (*perms)[5], int index, int* seq, int current, int len)
{
  if(current == len-1)
    memcpy(perms[index++], seq, len*sizeof(int));

  for(int i = current; i < len; ++i) {
    swap(seq, current, i);
    index = permutations(perms, index, seq, current+1, len);
    swap(seq, current, i);
  }
  return index;
}

int getParam(int* cmds, int pos, int cmd, int param)
{
  int mode = cmd/((int)pow(10, param+1)) % 10;
  if(mode == 0)
    return cmds[cmds[pos]];
  else if(mode == 1)
    return cmds[pos];

  fprintf(stderr, "Invalid mode\n");
  exit(1);
}

int execute(int* commands, int len, int* data, int len2)
{
  int p1, p2, p3, in, output = -1, j = 0;
  int* cmds = malloc(len*sizeof(int));
  memcpy(cmds, commands, len*sizeof(int));

  for(int i = 0; i < len;) {
    int cmd = cmds[i++];
    switch(cmd % 100) {
      case 1: // Add
        p1 = getParam(cmds, i++, cmd, 1);
        p2 = getParam(cmds, i++, cmd, 2);
        p3 = cmds[i++];
        cmds[p3] = p1 + p2;
        break;
      case 2: // Multiply
        p1 = getParam(cmds, i++, cmd, 1);
        p2 = getParam(cmds, i++, cmd, 2);
        p3 = cmds[i++];
        cmds[p3] = p1 * p2;
        break;
      case 3: // Input
        p1 = cmds[i++];
        if(j == len2) {
          printf("Please provide input: ");
          scanf("%d", &in);
          cmds[p1] = in;
        } else {
          cmds[p1] = data[j++];
        }
        break;
      case 4: // Output
        p1 = getParam(cmds, i++, cmd, 1);
        if(output != -1)
          printf("Result: %d\n", output);
        output = p1;
        break;
      case 5: // Jump if true
        p1 = getParam(cmds, i++, cmd, 1);
        p2 = getParam(cmds, i++, cmd, 2);
        if(p1)
          i = p2;
        break;
      case 6: // Jump if false
        p1 = getParam(cmds, i++, cmd, 1);
        p2 = getParam(cmds, i++, cmd, 2);
        if(!p1)
          i = p2;
        break;
      case 7: // Less than
        p1 = getParam(cmds, i++, cmd, 1);
        p2 = getParam(cmds, i++, cmd, 2);
        p3 = cmds[i++];
        cmds[p3] = p1 < p2;
        break;
      case 8: // Equals
        p1 = getParam(cmds, i++, cmd, 1);
        p2 = getParam(cmds, i++, cmd, 2);
        p3 = cmds[i++];
        cmds[p3] = p1 == p2;
        break;
      case 99: // Exit
        goto exit;
      default: // Error
        fprintf(stderr, "Something went wrong\n");
        return 1;
    }
  }
exit:
  free(cmds);
  return output;
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
  int count = 1;
  int dummy;
  // Read length of data
  while(fscanf(fp, "%d,", &dummy)>0)
    ++count;
  rewind(fp);

  int* commands = malloc(count*sizeof(int));
  count = 0;
  // Read data
  while(fscanf(fp, "%d,", &commands[count++])>0);

  int (*perms)[5] = malloc(120*5*sizeof(int));

  int data[2];
  int seq[5] = {0,1,2,3,4};
  int index = permutations(perms, 0, seq, 0, 5);
  int *perm, max = 0;
  for(int j = 0; j < 120; ++j) {
    perm = perms[j];
    data[1] = 0;
    for(int i = 0; i < 5; ++i) {
      data[0] = perm[i];
      data[1] = execute(commands, count, data, 2);
    }
    if (data[1] > max){
      max = data[1];
    }
  }

  printf("\nLargest output: %d\n", max);

  return 0;
}
