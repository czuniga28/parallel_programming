// Copyright 2023 <christopher.zunigarojas@ucr.ac.cr>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

#include "controller.h"

int main(int argc, char* argv[]) {
  // shared_data_t* shared = calloc(1, sizeof(shared_data_t));
  size_t thread_count = 0;
  if (argc == 2) {
    sscanf(argv[1], "%" SCNu64, &thread_count);
    controller_run(thread_count);
  } else {
    fprintf(stderr, "not expected arguments\n");
  } 
}
