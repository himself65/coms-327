#include "ca.h"
#include <stdio.h>

int in_range(const int input) {
  const int max_num = 100;
  const int min_num = 10;
  if (input >= min_num && input <= max_num) {
    return 0;
  } else {
    return 1;
  }
}

unsigned char aRule(struct ca_data *ca, int index) {
  if (ca->cells[index - 1] == 0) {
    if (ca->cells[index] == 0) {
      if (ca->cells[index + 1] == 0) {
        // 000
        return 0;
      } else {
        // 001
        return 1;
      }
    } else {
      if (ca->cells[index + 1] == 0) {
        // 010
        return 1;
      } else {
        // 011
        return 1;
      }
    }
  } else {
    if (ca->cells[index] == 0) {
      if (ca->cells[index + 1] == 0) {
        // 100
        return 0;
      } else {
        // 101
        return 1;
      }
    } else {
      if (ca->cells[index + 1] == 0) {
        // 110
        return 1;
      } else {
        // 111
        return 0;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 6) {
    printf("incorrect parameters length");
    return -1;
  }
  // step 1
  int size = atoi(argv[1]); // size of the cell
  if (in_range(size) != 0) {
    printf("incorrect size");
    return -1;
  }
  // step 2
  int total_state = atoi(argv[2]); // number of states

  // step 3
  int flag;
  if (strcmp(argv[3], "wrap") == 0) {
    flag = 1;
  } else if (strcmp(argv[3], "nowrap") == 0) {
    flag = 0;
  }
  // step 4
  int init_state = atoi(argv[4]);
  struct ca_data *ca = NULL;
  if (init_state >= -1 && init_state < total_state) {
    // specific values
    ca = create1DCA(size, init_state);
    if (ca == NULL) {
      printf("error when create 1dca\n");
      return -1;
    }
    ca->total_state = total_state;
    init1DCA(ca, init_state);
  } else {
    printf("incorrect input init state\n");
    return -1;
  }
  // step 5
  int step = atoi(argv[5]);
  display1DCA(ca);
  for (int i = 0; i < step; ++i) {
    // loop for emulate
    stepCA(ca, aRule, flag);
    display1DCA(ca);
  }
  return 0;
}
