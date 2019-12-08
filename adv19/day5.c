#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

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

int execute(int* cmds, int len)
{
  int p1, p2, p3, in;

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
        printf("Please provide input: ");
        scanf("%d", &in);
        cmds[p1] = in;
        break;
      case 4: // Output
        p1 = getParam(cmds, i++, cmd, 1);
        printf("Result: %d\n", p1);
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
        return 0;
      default: // Error
        fprintf(stderr, "Something went wrong\n");
        return 1;
    }
  }

  return 0;
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

  return execute(commands, count);
}
