#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;

void parser(int argc, char* argv[], opt* options);
void reader(int argc, char* argv[], opt* options);
void cat_no_arguments();

#endif  // S21_CAT_H_"
