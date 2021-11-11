#include <stdio.h>

int main(int argv, char** argv){
  int X[64][64];

  int i, j = 0;

  init();

  begin_recording();

  for(i = 0; i < 64; i++){
    for(j = 0; j < 64; j++){
      X[i][j] = 0;
    }
  }

  int pf1 = stop_recording();

  begin_recording();

  for(int j = 0; j < 64; j++){
    for(int i = 0; i < 64; i++){
      X[i][j] = 0;
    }
  }

  int pf2 = stop_recording();

  printf("Page-faults in loop 1: %d\nPage-faults in loop 2: %d\n", pf1, pf2);

  return 0;
}
