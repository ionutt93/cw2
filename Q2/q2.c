#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_CHAR '\0'

void split(char buffer[], char *names[], int *count) {
  char *token = strtok(buffer, ",");
  int str_count = 0;
  while (token != NULL) {
    names[str_count++] = token;
    token = strtok(NULL, ",");
  }

  *count = str_count;
}

void read_names(char *path, char *names[], int *count) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    perror("Error while opening the file.\n");
    exit(-1);
  }

  char buffer[100 * 6000];
  char ch;
  int char_count = 0;
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n') {
      buffer[char_count++] = ',';
    } else {
      buffer[char_count++] = ch;
    }
  }

  split(buffer, names, count);

  fclose(fp);
}

void write_names(char *path, char *names[], int count) {
  FILE *fp = fopen(path, "w");
  if (fp == NULL) {
    perror("Error while opening the file.\n");
    exit(-1);
  }

  int i;
  for (i = 0; i < count - 1; i++) {
    fprintf(fp, "%s%c", names[i], ',');
  }
  fprintf(fp, "%s", names[i]);

  fclose(fp);
}

void swap(char *names[], int i, int j) {
  char *temp = names[i];
  names[i] = names[j];
  names[j] = temp;
}

void bubble_sort(char *names[], int length) {
  int sorted = 0;
  while (sorted == 0) {
    sorted = 1;
    for (int i = 1; i < length; i++) {
      if (strcmp(names[i - 1], names[i]) > 0) {
        swap(names, i - 1, i);
        sorted = 0;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  char *input = "names.txt";
  char *output = "sorted_names.txt";

  if (argc == 2) {
    printf("%s\n", "One argument provided");
    input = argv[1];
  } else if (argc == 3) {
    printf("%s\n", "Two arguments provided");
    input = argv[1];
    output = argv[2];
  }

  printf("Input file: %s\n", input);
  printf("Output file: %s\n", output);

  char *names[6000];
  int names_count;
  read_names(input, names, &names_count);
  bubble_sort(names, names_count);
  write_names(output, names, names_count);
  return 0;
}