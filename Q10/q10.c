/* This program implements an algorithm which compresses a string of any length
by shortening every sequence of the same character to that character followed by
the number of repetitions. If the compressed
string is longer than the original, the function returns the original string.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct key_value {
  char key;
  int value;
} kv;

// reads a file into a dynamically allocated string string
char *read_file(char *path, int *text_length) {
  FILE *fp = fopen(path, "r");
  int size = 100;
  char *text = malloc(sizeof(char) * size);

  if (fp == NULL) {
    printf("Could not open file %s", path);
    exit(-1);
  }

  char ch;
  int i = 0;
  while ((ch = fgetc(fp)) != EOF) {
    text[i++] = ch;
    if (i == size - 2) {
      size = size * 2;
      text = realloc(text, sizeof(char) * size);
    }
  }
  text[i++] = '\0';
  *text_length = i;
  fclose(fp);

  return text;
}

// writes string to file
void write_file(char *path, kv myhash[], int kv_count) {
  FILE *fp = fopen(path, "w");

  for (int i = 0; i < kv_count; i++) {
    char key = myhash[i].key;
    int val = myhash[i].value;

    // if only one occurance of letter...
    if (val == 1) {
      //... print just the letter itself
      fprintf(fp, "%c", key);
    } else {
      // if the letter repeats, print the number of repetitions
      fprintf(fp, "%c%d", key, val);
    }
  }

  fclose(fp);
}

int main(int argc, char *argv[]) {
  char *input_path = "text.txt";
  char *output_path = "compressed.txt";
  // argv 1 - name of file to read in the text
  // argv 2 - name of file to write out the compressed text
  if (argc == 2) {
    printf("%s\n", argv[1]);
    input_path = argv[1];
  } else if (argc == 3) {
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    input_path = argv[1];
    output_path = argv[2];
  } else if (argc > 3) {
    puts("Invalid arguments");
    exit(-1);
  }

  int text_length;
  char *text = read_file(input_path, &text_length);
  kv myhash[text_length];

  char currentChar;
  int counter = 0;
  int kv_count = 0;

  currentChar = text[0];  // initialise currentChar to first letter of text
  // loop through each character of the text
  for (int i = 0; i <= text_length; i++) {
    // if character at index i is same as current character...
    if (text[i] == currentChar)
      counter++;  // then increase counter by 1
    else {
      // save the current character as the key in hashmap
      myhash[kv_count].key = currentChar;
      // save the counter to be the value i.e. how many
      // repetitions of that character there are
      myhash[kv_count].value = counter;
      // increase key-value count by 1
      kv_count++;

      currentChar = text[i];  // set new currentChar
      counter = 1;            // reset counter
    }
  }

  write_file(output_path, myhash, kv_count);
  return 0;
}
