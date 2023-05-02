#include "s21_grep.h"

int main(int argc, char* argv[]) {
  opt options = {0};
  char* pattern_mas[strlong] = {0};
  char* file_mas[strlong] = {0};
  int index_pat = 0;
  int index_file = 0;

  if (argc == 1)
    printf(
        "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
        "[-C[num]]");
  else {
    if (preliminary_search(argv, argc) == 0)
      short_parser(argv, pattern_mas, &index_pat);
    else
      parser(argc, argv, &options, pattern_mas, &index_pat);
  }

  creat_fmas(argc, argv, &index_file, file_mas);

  reader(index_file, file_mas, &options, pattern_mas, index_pat);

  free_memory(index_pat, pattern_mas);
  free_memory(index_file, file_mas);
  return 0;
}
int preliminary_search(char* argv[], int argc) {
  int count = 0;
  int num = 1;
  while (num < argc) {
    if (argv[num][0] == '-') {
      count++;
    }
    num++;
  }
  if (count > 0)
    return 1;
  else
    return 0;
}
void creat_fmas(int argc, char* argv[], int* index_file,
                char* file_mas[strlong]) {
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] != '\0') {
      file_mas[*index_file] = malloc((strlen(argv[i]) + 1) * sizeof(char));
      strcpy(file_mas[*index_file], argv[i]);
      *index_file += 1;
    }
  }
}
void creat_patmas(int* index_pat, char* pattern_mas[strlong], int number,
                  char* argv[], char* pat_name) {
  pattern_mas[*index_pat] = malloc((strlen(argv[number]) + 1) * sizeof(char));
  strcpy(pattern_mas[*index_pat], pat_name);
  memset(argv[number], '\0', strlen(argv[number]));
  *index_pat += 1;
}
void parser(int argc, char* argv[], opt* options, char* pattern_mas[strlong],
            int* index_pat) {
  int count = 1;
  int cfe = 0;
  while (count < argc) {
    if (argv[count][0] == '-') {
      for (size_t i = 1; i < strlen(argv[count]); i++) {
        if (argv[count][i] == 'e' || argv[count][i] == 'f') cfe++;
        sw_flags(argv[count][i], argv, options, count, pattern_mas, index_pat,
                 argc);
        chek_flags(argv[count][i], argv[count]);
      }
    }
    count++;
  }
  count = 1;
  while (count < argc) {
    if (argv[count][0] == '-') {
      search_pattern(argv, count, pattern_mas, index_pat, &cfe, argc);
      memset(argv[count], '\0', strlen(argv[count]));
    }
    count++;
  }
}
void sw_flags(char ch, char* argv[], opt* options, int count,
              char* pattern_mas[strlong], int* index_pat, int argc) {
  switch (ch) {
    case 'e':
      options->e = 1;
      pattern_e(argv, count, pattern_mas, index_pat, argc);
      break;
    case 'i':
      options->i = 1;
      break;
    case 'v':
      options->v = 1;
      break;
    case 'c':
      options->c = 1;
      break;
    case 'l':
      options->l = 1;
      break;
    case 'n':
      options->n = 1;
      break;
    case 'h':
      options->h = 1;
      break;
    case 's':
      options->s = 1;
      break;
    case 'f':
      options->f = 1;
      pattern_f(argv, count, pattern_mas, index_pat, argc);
      break;
    default:
      printf("invalid options\n");
      break;
  }
}
void chek_flags(char ch, char* argv) {
  int len = strlen(argv);
  int num_error = 0;
  int flag_error = 0;
  ch = argv[1];
  for (int i = 1; i < len && flag_error == 0; i++) {
    if (argv[i] == '-' && ch != 'e') {
      num_error = i;
      flag_error = 1;
    }
  }
  if (flag_error == 1) {
    printf("unrecognized option -");
    for (int i = num_error; i < len; i++) {
      printf("%c", argv[i]);
    }
    exit(1);
  }
}
void pattern_e(char* argv[], int number, char* pattern_mas[strlong],
               int* index_pat, int argc) {
  int k = -1;
  for (size_t i = 1; i < strlen(argv[number]) && k == -1; i++) {
    if (argv[number][i] == 'e' && argv[number][i + 1] == '\0' &&
        number == argc - 1) {
      fprintf(stderr, "option requires an argument -- e\n");
      exit(1);
    } else {
      if (argv[number][i] == 'e') {
        k = i;
      }
    }
  }
  if (argv[number][k + 1] == '\0') {
    creat_patmas(index_pat, pattern_mas, number + 1, argv, argv[number + 1]);
    memset(argv[number], '\0', strlen(argv[number]));
  } else {
    char string[strlong] = " ";
    int m = 0;
    int l = k + 1;
    while (argv[number][l] != '\0') {
      string[m] = argv[number][l];
      m++;
      l++;
    }
    creat_patmas(index_pat, pattern_mas, number, argv, string);
  }
}
void pattern_f(char* argv[], int number, char* pattern_mas[strlong],
               int* index_pat, int argc) {
  int k = -1;
  char file_name[strlong] = "";
  for (size_t i = 1; i < strlen(argv[number]) && k == -1; i++) {
    if (argv[number][i] == 'f' && argv[number][i + 1] == '\0' &&
        number == argc - 1) {
      fprintf(stderr, "option requires an argument -- f\n");
      exit(1);
    } else {
      if (argv[number][i] == 'f') {
        k = i;
      }
    }
  }
  if (argv[number][k + 1] == '\0') {
    read_fpat(argv, argv[number + 1], index_pat, pattern_mas);
    memset(argv[number + 1], '\0', strlen(argv[number + 1]));
    memset(argv[number], '\0', strlen(argv[number]));

  } else {
    int m = 0;
    int l = k + 1;
    while (argv[number][l] != '\0') {
      file_name[m] = argv[number][l];
      m++;
      l++;
    }
    read_fpat(argv, file_name, index_pat, pattern_mas);
    memset(argv[number], '\0', strlen(argv[number]));
  }
}
void read_fpat(char* argv[], char* file_name, int* index_pat,
               char* pattern_mas[strlong]) {
  FILE* fp = NULL;
  int len = 0;
  char string[strlong] = "";
  fp = fopen(file_name, "r");
  if (fp != NULL) {
    while (fgets(string, strlong, fp) != NULL) {
      len = strlen(string);
      if (string[len - 1] == '\n' && len > 1) {
        string[len - 1] = '\0';
      }
      pattern_mas[*index_pat] = malloc((strlen(string) + 1) * sizeof(char));
      strcpy(pattern_mas[*index_pat], string);
      *index_pat += 1;
    }
    fclose(fp);
  } else {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], file_name);
    exit(1);
  }
}
void search_pattern(char* argv[], int count, char* pattern_mas[strlong],
                    int* index_pat, int* cfe, int argc) {
  if (*cfe == 0 && ((argv[1][0] != '-') && (argv[1][0] != '\0')) && (count)) {
    creat_patmas(index_pat, pattern_mas, 1, argv, argv[1]);
    *cfe += 1;
  }
  if (*cfe == 0 && ((argv[count + 1][0] != '-') && (count != argc - 2))) {
    creat_patmas(index_pat, pattern_mas, count + 1, argv, argv[count + 1]);
    *cfe += 1;
  }
}
void short_parser(char* argv[], char* pattern_mas[strlong], int* index_pat) {
  creat_patmas(index_pat, pattern_mas, 1, argv, argv[1]);
}
void reader(int index_file, char* file_mas[strlong], opt* options,
            char* pattern_mas[strlong], int index_pat) {
  regex_t myreg;
  int count_line = 0;
  int current_File = 1;
  char string[strlong] = " ";
  FILE* fp = NULL;
  while (current_File < index_file) {
    fp = fopen(file_mas[current_File], "r");
    current_File++;
    if (fp != NULL) {
      int num_line = 1;
      int count_string = 0;
      while (fgets(string, strlong, fp) != NULL) {
        count_line = 0;
        for (int i = 0; i < index_pat && count_line == 0; i++) {
          reg(myreg, options, string, pattern_mas[i], &count_line);
        }
        if (options->v) {
          func_v(&count_line);
        }
        if (options->c || options->l) {
          func_lc(count_line, &count_string);
        }
        if (count_line > 0 && !options->c && !options->l) {
          output(file_mas[current_File - 1], index_file, string, num_line,
                 options);
        }
        num_line++;
      }
      if (options->c || options->l) {
        output_lc(options, count_string, file_mas[current_File - 1],
                  index_file);
      }
      fclose(fp);
    } else {
      if (!options->s) {
        fprintf(stderr, "%s: %s: No such file or directory\n", file_mas[0],
                file_mas[current_File - 1]);
      }
    }
  }
}
void reg(regex_t myreg, opt* options, char* string, char* pattern,
         int* count_line) {
  int rez = 0;
  if (strcmp(pattern, ".") == 0) {
    rez = regcomp(&myreg, pattern, REG_NEWLINE);
  } else {
    rez = regcomp(&myreg, pattern,
                  options->i ? REG_EXTENDED | REG_ICASE : REG_EXTENDED);
  }
  if (rez == 0) {
    if ((regexec(&myreg, string, 0, NULL, 0) == 0)) {
      *count_line = 1;
    }
  }
  regfree(&myreg);
}
void func_v(int* count_line) {
  if (*count_line == 1) {
    *count_line = 0;
  } else {
    *count_line = 1;
  }
}
void func_lc(int count_line, int* count_string) {
  if (count_line == 1) {
    *count_string += 1;
  }
}
void output(char* file_mas, int index_file, char* string, int num_line,
            opt* options) {
  int len = strlen(string);
  if (options->h) {
    index_file = 2;
  }
  if (options->n) {
    if (index_file == 2) {
      printf("%d:%s", num_line, string);
    }
    if (index_file > 2) {
      printf("%s:%d:%s", file_mas, num_line, string);
    }
    if (string[len - 1] != '\n') {
      printf("\n");
    }
  } else {
    if (index_file == 2) {
      printf("%s", string);
    }
    if (index_file > 2) {
      printf("%s:%s", file_mas, string);
    }
    if (string[len - 1] != '\n') {
      printf("\n");
    }
  }
}
void output_lc(opt* options, int count_string, char* file_mas, int index_file) {
  if (options->h) {
    index_file = 2;
  }
  if (options->c && options->l) {
    if (count_string > 0) {
      count_string = 1;
    }
  }
  if (options->c) {
    if (index_file == 2) {
      printf("%d\n", count_string);
    }
    if (index_file > 2) {
      printf("%s:%d\n", file_mas, count_string);
    }
  }
  if (options->l && count_string > 0) {
    printf("%s\n", file_mas);
  }
}
void free_memory(int size, char* massiv[strlong]) {
  for (int i = 0; i < size; i++) {
    free(massiv[i]);
  }
}
