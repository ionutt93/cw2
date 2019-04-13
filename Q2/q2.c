#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NULL_CHAR '\0'

void split(char buffer[], char *names[], int *count)
{
	char *token = strtok(buffer, ",");
	int str_count = 0;
	while (token != NULL)
	{
		names[str_count++] = token;
		token = strtok(NULL, ",");
	}

	*count = str_count;
}

void read_names(char *path, char *names[], int *count)
{
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(-1);
	}

	char buffer[100 * 6000];
	char ch;
	int char_count = 0;
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
		{
			buffer[char_count++] = ',';
		}
		else
		{
			buffer[char_count++] = ch;
		}
	}

	split(buffer, names, count);

	fclose(fp);
}

void write_names(char *path, char *names[], int count)
{
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(-1);
	}

	int i;
	for (i = 0; i < count - 1; i++)
	{
		fprintf(fp, "%s%c", names[i], ',');
	}
	fprintf(fp, "%s", names[i]);

	fclose(fp);
}

void swap(char *names[], int i, int j)
{
	char *temp = names[i];
	names[i] = names[j];
	names[j] = temp;
}

void bubble_sort(char *names[], int length)
{
	int sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		for (int i = 1; i < length; i++)
		{
			if (strcmp(names[i - 1], names[i]) > 0)
			{
				swap(names, i - 1, i);
				sorted = 0;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		printf("%s\n", argv[1]);
		printf("%s\n", argv[2]);

		char *names[6000];
		int names_count;
		read_names(argv[1], names, &names_count);
		bubble_sort(names, names_count);
		write_names(argv[2], names, names_count);
		return 0;
	}
	else
	{
		printf("%s\n", "Please provide both the input file and output file");
		return -1;
	}
}