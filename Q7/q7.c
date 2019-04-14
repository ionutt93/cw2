/* This program redacts redactable words from a given block of text.
A text file containing a pre-defined set of words to redact is also passed in as
a program argument. Once all the redactable words have been redacted, the new
redacted text is saved in an output file*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char redact_words[10][30];
FILE *outfile;

void getRedactWords(char *red_file) {
  FILE *file = fopen(red_file, "r");
  char *ptok = NULL;

  if (file != NULL) {
    char line[30];
    int i = 0;

    while (fgets(line, 30, file) != NULL) /* read a line */
    {
      int len = strlen(line);
      if (line[len - 1] == '\n') line[len - 1] = '\0';

      ptok = strtok(line, " ");
      while (ptok != NULL) {
        strcpy(redact_words[i], ptok);

        ptok = strtok(NULL, " ");
        i++;
      }
    }
    fclose(file);
  } else {
    perror(red_file);
  }
  printf("Words to replace:\n");
  int arr_size = sizeof(redact_words) / sizeof(redact_words[0]);
  for (int i = 0; i < arr_size; i++) printf("%s\n", redact_words[i]);
}

// boolean function to check whether the arg 'word' is in 'redact_words'
int isRedactable(char *word) {
  char text_word[30];
  //	char red_word[30];
  sprintf(text_word, "%s\0", word);
  int len_word = strlen(text_word);
  // for (int i = 0; i < len_word; i++)
  //	text_word[i] = tolower(text_word[i]);

  for (int i = 0; i < 10; i++) {
    if (strcmp(text_word, redact_words[i]) == 0) {
      return len_word;
    }
  }
  return 0;
}

void outputToFile(char *text) {
  if (outfile == NULL) {
    perror("Error while opening the file.\n");
    exit(-1);
  }

  fputs(text, outfile);
}

int main(int argc, char *argv[]) {
  char ch;
  FILE *fp;
  char cur_path[] = "";
  char r_txt_file[100] = "debate1.txt";
  char r_redact_file[100] = "redact1.txt";
  char w_redacted_txt[100] = "redacted_out.txt";
  char line[500];
  char replaced_line[500] = "\0";
  char extra_char[2] = "\0";
  char *token;
  char temp_tok[30];
  int appendNewline = 0;

  // argv 1 - name of file to read in text
  // argv 2 - name of file to read in list of words to redact
  // argv 3 - name of file to write out the redacted text
  if (argc == 3) {
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    strcpy(r_txt_file, cur_path);
    strcat(r_txt_file, argv[1]);
    strcpy(r_redact_file, cur_path);
    strcat(r_redact_file, argv[2]);
  } else if (argc == 4) {
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    printf("%s\n", argv[3]);
    strcpy(r_txt_file, cur_path);
    strcat(r_txt_file, argv[1]);
    strcpy(r_redact_file, cur_path);
    strcat(r_redact_file, argv[2]);
    strcpy(w_redacted_txt, cur_path);
    strcat(w_redacted_txt, argv[3]);
  }

  getRedactWords(r_redact_file);

  printf("Input file is %s\n", r_txt_file);

  outfile = fopen(w_redacted_txt, "w+");

  fp = fopen(r_txt_file, "r");
  if (fp == NULL) {
    perror("Error while opening the file.\n");
    exit(-1);
  }

  printf("\nSentence to redact (substitute with *):\n");
  while (fgets(line, 500, fp) != NULL) {
    token = strtok(line, " ");

    int word_len = isRedactable(token);
    int x;
    char asterisk[30];
    if (word_len > 0) {
      for (x = 0; x < word_len; x++) asterisk[x] = '*';
      asterisk[x] = '\0';

      strcat(replaced_line, asterisk);
    } else {
      strcat(replaced_line, token);
    }
    strcat(replaced_line, " ");

    // get other tokens
    while (token != NULL) {
      token = strtok(NULL, " ");

      if (token != NULL) {
        // has word got extra , or .
        strcpy(temp_tok, token);
        int last_char = strlen(temp_tok) - 1;
        if (temp_tok[last_char] == '\n') {
          last_char--;
          appendNewline = 1;
        }

        if (isalpha(temp_tok[last_char]) == 0) {
          if (isdigit(temp_tok[last_char]) == 0) {
            extra_char[0] = temp_tok[last_char];
            temp_tok[last_char] = '\0';
          }
        }

        word_len = isRedactable(temp_tok);
        asterisk[word_len];

        if (word_len > 0) {
          for (x = 0; x < word_len; x++) asterisk[x] = '*';
          asterisk[x] = '\0';

          strcat(replaced_line, asterisk);
          if (extra_char[0] != '\0') {
            strcat(replaced_line, extra_char);
          }
          if (appendNewline == 1) {
            strcat(replaced_line, "\n");
          }
        } else {
          strcat(replaced_line, token);
        }
        strcat(replaced_line, " ");
        extra_char[0] = '\0';
        appendNewline = 0;
      } else {
        // remove last space
        replaced_line[strlen(replaced_line) - 1] = '\0';
      }
    }
    printf("%s", replaced_line);
    outputToFile(replaced_line);

    replaced_line[0] = '\0';
  }
  fclose(fp);
  fclose(outfile);

  return 0;
}
