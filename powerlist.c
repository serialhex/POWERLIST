// POWERLIST.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Error checking...
#define TestMsg(test, message, ...) do { \
  if ((test)) { printf((message), __VA_ARGS__); goto fail; } \
  } while (0)

// Some Data types...
// Actually make this dynamic in a real program...
#define max_str 32
#define max_lines 1024

typedef struct SuperStringArray {
  int lines;
  int counter;
  char str[max_lines][max_str];
} SuperStringArray;

SuperStringArray* make_super_string_array(char* str) {
  SuperStringArray* ssa = (SuperStringArray*)malloc(sizeof(SuperStringArray));
  ssa->counter = 0;

  char* line = strtok(str, "\n");
  for (ssa->lines = 0; ssa->lines < max_lines; ssa->lines++) {
    if (line == NULL) {
      break;
    }

    strcpy(ssa->str[ssa->lines], line);

    // prep for next loop
    line = strtok(NULL, "\n");
  }
  ssa->lines--;

  return ssa;
}

void print_super_string_array(SuperStringArray* ssa) {
  for (int i = 0; i < ssa->lines; i++) {
    printf("%s\n", ssa->str[i]);
  }
}

bool at_end_p(SuperStringArray** ssaa, const int total) {
  for (int i = 0; i < total; i++) {
    if (ssaa[i]->lines != ssaa[i]->counter) {
      return false;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  // Sad path
  TestMsg(argc < 3, "Sorry, need at least 2 files\n");

  const int total_files = argc - 1;

  // Setting up the Super String Array Array!
  SuperStringArray** SSAA = (SuperStringArray**)malloc(total_files * sizeof(SuperStringArray));
  TestMsg(!SSAA, "SUPER STRING ARRAY ARRAY FAIL!!!");


  // Read files in
  for (int i = 0; i < total_files; i++) {
    // Get File
    FILE* f = fopen(argv[i+1], "r");

    // Read it in...
    char* buffer = 0;
    int length;
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);
    if (buffer) {
      fread(buffer, 1, length, f);
    }
    buffer[length] = '\0';

    SSAA[i] = make_super_string_array(buffer);

    fclose(f);
  }

  // Meat & potatoes!
  bool inc_next = false;
  while (!at_end_p(SSAA, total_files)) {

    for (int i = 0; i < total_files; i++) {
      SuperStringArray* ssa = SSAA[i];

      if (inc_next) {
        if (ssa->counter + 1 > ssa->lines) {
          ssa->counter = 0;
          inc_next = true;
        } else {
          ssa->counter++;
          inc_next = false;
        }
      }

      printf("%s", ssa->str[ssa->counter]);
    }
    puts("");
    inc_next = true;
  }

success:
  return 0;

fail:
  return 1;
}

