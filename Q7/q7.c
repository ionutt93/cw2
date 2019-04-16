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

// // read redacted words
// void getRedactWords(char *red_file) {
//   FILE *file = fopen(red_file, "r");
//   char *ptok = NULL;

//   if (file != NULL) {
//     char line[30];
//     int i = 0;

//     while (fgets(line, 30, file) != NULL) /* read a line */
//     {
//       int len = strlen(line);
//       if (line[len - 1] == '\n') line[len - 1] = '\0';

//       ptok = strtok(line, " ");
//       while (ptok != NULL) {
//         strcpy(redact_words[i], ptok);

//         ptok = strtok(NULL, " ");
//         i++;
//       }
//     }
//     fclose(file);
//   } else {
//     perror(red_file);
//   }
//   printf("Words to replace:\n");
//   int arr_size = sizeof(redact_words) / sizeof(redact_words[0]);
//   for (int i = 0; i < arr_size; i++) printf("%s\n", redact_words[i]);
// }

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
    // if character or digit
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
        (ch >= '0' && ch <= '9')) {
      buffer[buffer_length++] = ch;
    } else {
      for (int i = 0; i < buffer_length; i++) {
        tokens[tokens_length][i] = buffer[i];
      }
      tokens[tokens_length][buffer_length] = '\0';

      tokens_length++;
      buffer_length = 0;

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

void redact_word(char *word) {
  int i = 0;
  while (word[i] != '\0') {
    word[i++] = '*';
  }
}

int equal(char *w1, char *w2) {
  return strcasecmp(w1, w2);

  // int i = 0;
  // while (tolower(w1[i]) == tolower(w2[i]) && w1[i] != '\0' && w2[i] != '\0')
  // {
  //   i++;
  // }

  // if (w1[i] != '\0' && w2[i] != '\0') {
  //   return 1;
  // }

  // return 0;
}

int is_redactable(char *word, char *redactable[], int redactable_count) {
  for (int i = 0; i < redactable_count; i++) {
    if (equal(word, redactable[i]) == 0) {
      return 1;
    }
  }
  return 0;
}

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

// // checks if word is redactable
// int isRedactable(char *word, char *redact_words[]) {
//   int length = (int)(sizeof(redact_words) / sizeof(redact_words[0]));

//   for (int i = 0; i < length; i++) {
//     if (strcasecmp(word, redact_words[i]) == 0) {
//       return strlen(word);
//     }
//   }
//   return 0;
// }

// char *asterisk_str(int n) {
//   char *x = malloc(sizeof(char) * (n + 1));
//   for (int i = 0; i < n; i++) {
//     x[i] = '*';
//   }
//   return x;
// }

// // redact
// char *redact(char *redact_words[], char *text) {
//   char *redactedText = malloc(sizeof(text));
//   char *text_words[1000];
//   int text_words_count;
//   splitWords(text, " ", text_words, &text_words_count);

//   for (int i = 0; i < text_words_count - 1; i++) {
//     int n = isRedactable(text_words[i], redact_words);
//     if (n > 0) {
//       char *x = asterisk_str(n);
//       strcat(redactedText, x);
//       free(x);
//     } else {
//       strcat(redactedText, text_words[i]);
//     }
//     strcat(redactedText, " ");
//   }

//   int n = isRedactable(text_words[text_words_count - 1], redact_words);
//   if (n > 0) {
//     char *x = asterisk_str(n);
//     strcat(redactedText, x);
//     free(x);
//   } else {
//     strcat(redactedText, text_words[text_words_count - 1]);
//   }

//   return redactedText;
// }

int main(int argc, char *argv[]) {
  char *input_redacted_words_path;
  char *input_text_path;
  char *output_text_path;

  if (argc == 1) {
    input_text_path = "debate1.txt";
    input_redacted_words_path = "redact1.txt";
    output_text_path = "redacted_out.txt";
  } else if (argc == 3) {
    input_text_path = argv[1];
    input_redacted_words_path = argv[2];
    output_text_path = "redacted_out.txt";
  } else if (argc == 4) {
    input_text_path = argv[1];
    input_redacted_words_path = argv[2];
    output_text_path = argv[3];
  }

  int text_length;
  int redact_words_text_length;
  char *text = read_file("debate.txt", &text_length);
  char *redact_words_text = read_file("redact.txt", &redact_words_text_length);

  char *redacted_txt_output[text_length];
  int redacted_txt_output_length;

  redact_text(text, text_length, redact_words_text, redact_words_text_length,
              redacted_txt_output, &redacted_txt_output_length);

  write_file("redacted_out.txt", redacted_txt_output,
             redacted_txt_output_length);

  return 0;
}

// int main(int argc, char *argv[]) {
//   char ch;
//   FILE *fp;
//   char cur_path[] = "";
//   char r_txt_file[100] = "debate1.txt";
//   char r_redact_file[100] = "redact1.txt";
//   char w_redacted_txt[100] = "redacted_out.txt";
//   char line[500];
//   char replaced_line[500] = "\0";
//   char extra_char[2] = "\0";
//   char *token;
//   char temp_tok[30];
//   int appendNewline = 0;

//   // argv 1 - name of file to read in text
//   // argv 2 - name of file to read in list of words to redact
//   // argv 3 - name of file to write out the redacted text
//   if (argc == 3) {
//     printf("%s\n", argv[1]);
//     printf("%s\n", argv[2]);
//     strcpy(r_txt_file, cur_path);
//     strcat(r_txt_file, argv[1]);
//     strcpy(r_redact_file, cur_path);
//     strcat(r_redact_file, argv[2]);
//   } else if (argc == 4) {
//     printf("%s\n", argv[1]);
//     printf("%s\n", argv[2]);
//     printf("%s\n", argv[3]);
//     strcpy(r_txt_file, cur_path);
//     strcat(r_txt_file, argv[1]);
//     strcpy(r_redact_file, cur_path);
//     strcat(r_redact_file, argv[2]);
//     strcpy(w_redacted_txt, cur_path);
//     strcat(w_redacted_txt, argv[3]);
//   }

//   getRedactWords(r_redact_file);

//   printf("Input file is %s\n", r_txt_file);

//   outfile = fopen(w_redacted_txt, "w+");

//   fp = fopen(r_txt_file, "r");
//   if (fp == NULL) {
//     perror("Error while opening the file.\n");
//     exit(-1);
//   }

//   printf("\nSentence to redact (substitute with *):\n");
//   while (fgets(line, 500, fp) != NULL) {
//     token = strtok(line, " ");

//     int word_len = isRedactable(token);
//     int x;
//     char asterisk[30];
//     if (word_len > 0) {
//       for (x = 0; x < word_len; x++) asterisk[x] = '*';
//       asterisk[x] = '\0';

//       strcat(replaced_line, asterisk);
//     } else {
//       strcat(replaced_line, token);
//     }
//     strcat(replaced_line, " ");

//     // get other tokens
//     while (token != NULL) {
//       token = strtok(NULL, " ");

//       if (token != NULL) {
//         // has word got extra , or .
//         strcpy(temp_tok, token);
//         int last_char = strlen(temp_tok) - 1;
//         if (temp_tok[last_char] == '\n') {
//           last_char--;
//           appendNewline = 1;
//         }

//         if (isalpha(temp_tok[last_char]) == 0) {
//           if (isdigit(temp_tok[last_char]) == 0) {
//             extra_char[0] = temp_tok[last_char];
//             temp_tok[last_char] = '\0';
//           }
//         }

//         word_len = isRedactable(temp_tok);
//         asterisk[word_len];

//         if (word_len > 0) {
//           for (x = 0; x < word_len; x++) asterisk[x] = '*';
//           asterisk[x] = '\0';

//           strcat(replaced_line, asterisk);
//           if (extra_char[0] != '\0') {
//             strcat(replaced_line, extra_char);
//           }
//           if (appendNewline == 1) {
//             strcat(replaced_line, "\n");
//           }
//         } else {
//           strcat(replaced_line, token);
//         }
//         strcat(replaced_line, " ");
//         extra_char[0] = '\0';
//         appendNewline = 0;
//       } else {
//         // remove last space
//         replaced_line[strlen(replaced_line) - 1] = '\0';
//       }
//     }
//     printf("%s", replaced_line);
//     outputToFile(replaced_line);

//     replaced_line[0] = '\0';
//   }
//   fclose(fp);
//   fclose(outfile);

//   return 0;
// }
