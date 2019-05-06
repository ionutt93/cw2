/* This program redacts redactable words from a given block of text.
A text file containing a pre-defined set of words to redact is also passed in as
a program argument. Once all the redactable words have been redacted, the new
redacted text is saved in an output file*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char redact_words[10][30];
FILE *outfile;

// reads a file into a char buffer
char *read_file(char *path, int *length) {
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

  *length = i;
  fclose(fp);

  return text;
}

// writes char array to file
void write_file(char *path, char *words[], int count) {
  FILE *fp = fopen(path, "w");

  if (fp == NULL) {
    printf("Could not open file %s", path);
    exit(-1);
  }

  for (int i = 0; i < count; i++) {
    fputs(words[i], fp);
  }

  fclose(fp);
}

// tokenizes text into an array of words, with the option of saving the
// separators as well
void tokenize_text(char *text, int length, int save_separators, char *tokens[],
                   int *tokens_count) {
  int i = 0;
  int tokens_length = 0;
  char ch;
  char buffer[100];
  int buffer_length = 0;

  ch = text[i++];

  for (int i = 0; i < length; i++) {
    tokens[i] = malloc(sizeof(char) * 100);
  }

  while (ch != '\0') {
    // if character or digit add it to the buffer
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
        (ch >= '0' && ch <= '9')) {
      buffer[buffer_length++] = ch;
    } else {
      // move the buffer contents into a token, as the word is complete
      for (int i = 0; i < buffer_length; i++) {
        tokens[tokens_length][i] = buffer[i];
      }
      tokens[tokens_length][buffer_length] = '\0';

      tokens_length++;
      buffer_length = 0;

      // if specified, we can include the separators as tokens as well
      if (save_separators == 1) {
        tokens[tokens_length][0] = ch;
        tokens[tokens_length][1] = '\0';
        tokens_length++;
      }
    }
    ch = text[i++];
  }

  *tokens_count = tokens_length;
}

// replaces every character in the word with *
void redact_word(char *word) {
  int i = 0;
  while (word[i] != '\0') {
    word[i++] = '*';
  }
}

// check if word is redactable or not
int is_redactable(char *word, char *redactable[], int redactable_count) {
  for (int i = 0; i < redactable_count; i++) {
    if (strcasecmp(word, redactable[i]) == 0) {
      return 1;
    }
  }
  return 0;
}

// tokenizes text and redacts the redactable words
void redact_text(char *text, int text_length, char *redact_words,
                 int words_length, char *tokenized_text[], int *output_length) {
  // tokenize the input text
  // char *tokenized_text[text_length];
  int tokenized_text_length = 0;
  tokenize_text(text, text_length, 1, tokenized_text, &tokenized_text_length);

  // tokenize the redacted words text
  char *tokenized_redact_words[words_length];
  int tokenized_redact_words_length;
  tokenize_text(redact_words, words_length, 0, tokenized_redact_words,
                &tokenized_redact_words_length);

  // for each token, if it is redactable replace it with *
  for (int i = 0; i < tokenized_text_length; i++) {
    if (is_redactable(tokenized_text[i], tokenized_redact_words,
                      tokenized_redact_words_length) == 1) {
      redact_word(tokenized_text[i]);
    }
  }

  *output_length = tokenized_text_length;
}

int main(int argc, char *argv[]) {
  char *input_path = "debate.txt";
  char *input_redact_path = "redact.txt";
  char *output_path = "redacted_out.txt";

  if (argc == 3) {
    input_path = argv[1];
    input_redact_path = argv[2];
  } else if (argc == 4) {
    input_path = argv[1];
    input_redact_path = argv[2];
    output_path = argv[3];
  }

  printf("Input text file: %s\n", input_path);
  printf("Input redact file: %s\n", input_redact_path);
  printf("Output file: %s\n", output_path);

  // read the text and redactable words
  int text_length;
  int redact_words_text_length;
  char *text = read_file(input_path, &text_length);
  char *redact_words_text =
      read_file(input_redact_path, &redact_words_text_length);

  char *redacted_txt_output[text_length];
  int redacted_txt_output_length;

  redact_text(text, text_length, redact_words_text, redact_words_text_length,
              redacted_txt_output, &redacted_txt_output_length);

  // write redacted words to a file
  write_file(output_path, redacted_txt_output, redacted_txt_output_length);

  return 0;
}