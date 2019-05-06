/* This program uses the quick sort method to sort an array of names
   into alphabetical order in C */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// function to swap two elements in an array indexed by a and b
void swap(char *array[], int a, int b) {
  char *temp;

  temp = array[a];
  array[a] = array[b];
  array[b] = temp;
}

// function which uses the quick sort algorithm. The implementation below is an
// example of the algorithm being used to sort an array of names into
// alphabetical order
void quickSort(char *array[], int left, int right) {
  int pivot;
  int i;
  int j;
  const char *key;

  // end conditional for recursion
  if (right - left == 1) {
    if (strcmp(array[left], array[right]) > 0) {
      printf("Only one entry: ");
      swap(array, left, right);
    }
    return;
  }

  // choose mid point for the pivot
  pivot = (left + right) / 2;
  key = array[pivot];
  printf("Sorting from %d to %d: pivot (midpoint) is at %d, '%s'\n", left,
         right, pivot, key);

  // put the pivot key at the left of the list
  swap(array, left, pivot);

  i = left + 1;
  j = right;

  while (i < j) {
    while (i <= right && strcmp(array[i], key) < 0) {
      // leave the parts on the left of "key" in place if they are smaller than
      // or equal to "key"
      i++;
    }
    while (j >= left && strcmp(array[j], key) > 0) {
      // leave the parts on the right of "key" in place if they are greater than
      // "key"
      j--;
    }
    if (i < j) {
      // "array[i]" is greater than "key", and "array[j]" is less than or equal
      // to "key", so swap them
      printf("Out of order: '%s' > '%s', but %d < %d: ", array[i], array[j], i,
             j);
      swap(array, i, j);
    }
  }

  // put the pivot key back between the two sorted halves
  printf("Putting the pivot back: ");
  swap(array, left, j);

  if (left < j - 1) {
    printf("Sub-sorting lower entries.\n");
    // sort the left half using this function recursively
    quickSort(array, left, j - 1);
  }
  if (j + 1 < right) {
    printf("Sub-sorting upper entries.\n");
    // sort the right half using this function recursively
    quickSort(array, j + 1, right);
  }
}

void saveOrderedNames(char *w_file, char *name[], int n) {
  FILE *fp;
  int i;

  fp = fopen(w_file, "w+");
  if (fp == NULL) {
    perror("Error while opening the file.\n");
    exit(-1);
  }

  for (i = 0; i < n; i++) {
    if (i == n - 1)
      fputs(name[i], fp);
    else
      fprintf(fp, "%s%c", name[i], ',');

    printf("%d: %s\n", i, name[i]);
  }
  fclose(fp);
}

int main(int argc, char *argv[]) {
  // argv 1 - name of file to read in a list of names
  // argv 2 - name of file to write out the sorted list of names

  char ch;
  FILE *fp;
  char cur_path[200];
  char r_file[200] = "names.txt";
  char w_file[200] = "sorted_names.txt";
  char line[46450];
  char *token;
  char *name[5163];

  if (getcwd(cur_path, sizeof(cur_path)) != NULL) {
    fprintf(stdout, "Current working dir: %s\n", cur_path);
    strcat(cur_path, "/");
  } else
    perror("getcwd() error");

  if (argc == 2) {
    printf("%s\n", argv[1]);
    strcpy(r_file, cur_path);
    strcat(r_file, argv[1]);
  } else if (argc == 3) {
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    strcpy(r_file, cur_path);
    strcat(r_file, argv[1]);
    strcpy(w_file, cur_path);
    strcat(w_file, argv[2]);
  }

  printf("Input file is %s\n", r_file);

  fp = fopen(r_file, "r");
  if (fp == NULL) {
    perror("Error while opening the file.\n");
    exit(-1);
  }

  // printf("The contents of %s file are:\n", argv[1]);
  int i = 0;
  while ((ch = fgetc(fp)) != EOF) {
    if (ch != '\n')  // // ignore new line char
      line[i] = ch;
    //        printf("%c", ch);
    i++;
  }
  fclose(fp);

  // get the first token
  token = strtok(line, ",");

  i = 0;
  // get other tokens
  while (token != NULL) {
    name[i] = token;
    token = strtok(NULL, ",");
    i++;
  }

  int name_size = sizeof(name) / sizeof(name[0]);

  for (int i = 0; i < name_size; i++) {
    printf("%d: %s\n", i, name[i]);
  }

  printf("Before sort:\n\n");
  quickSort(name, 0, name_size - 1);
  printf("\nAfter sort:\n\n");
  saveOrderedNames(w_file, name, name_size);
  printf("\nOutput file of sorted names is %s\n", w_file);

  return 0;
}
