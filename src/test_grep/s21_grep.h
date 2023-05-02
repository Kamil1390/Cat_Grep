#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define strlong 1024

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} opt;

int preliminary_search(char* argv[], int argc);
void parser(int argc, char* argv[], opt* options, char* pattern_mas[strlong],
            int* index_pat);
void short_parser(char* argv[], char* pattern_mas[strlong], int* index_pat);
void creat_fmas(int argc, char* argv[], int* index_file,
                char* file_mas[strlong]);
void creat_patmas(int* index_pat, char* pattern_mas[strlong], int number,
                  char* argv[], char* pat_name);
void sw_flags(char ch, char* argv[], opt* options, int count,
              char* pattern_mas[strlong], int* index_pat, int argc);
void chek_flags(char ch, char* argv);
void pattern_e(char* argv[], int number, char* pattern_mas[strlong],
               int* index_pat, int argc);
void pattern_f(char* argv[], int number, char* pattern_mas[strlong],
               int* index_pat, int argc);
void read_fpat(char* argv[], char* file_name, int* index_pat,
               char* pattern_mas[strlong]);
void search_pattern(char* argv[], int count, char* pattern_mas[strlong],
                    int* index_pat, int* cfe, int argc);
void reader(int index_file, char* file_mas[strlong], opt* options,
            char* pattern_mas[strlong], int index_pat);
void reg(regex_t myreg, opt* options, char* string, char* pattern,
         int* count_line);
void func_v(int* count_line);
void func_lc(int count_line, int* count_string);
void output(char* file_mas, int index_file, char* string, int num_line,
            opt* options);
void output_lc(opt* options, int count_string, char* file_mas, int index_file);
void free_memory(int size, char* massiv[strlong]);

#endif  // S21_GREP_H_"
