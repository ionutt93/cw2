/* This program uses the bubble sort method to sort an array of names into alphabetical order in C*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int bubbleSortNames(char *name[], int num_names) {
    int i, j, cmp;
    //char tmp[15];
    char *tmp = NULL;
    
    if (num_names <= 1)
        return 0; // Already sorted
    
    for (i = 0; i < num_names; i++)
    {
        for (j = 0; j < num_names-1; j++)
        {
            cmp = strcmp(name[j], name[j+1]);
            
            if (cmp > 0)
            {
                //strcpy(tmp, name[j+1]);
                tmp = name[j+1];
                //strcpy(name[j+1], name[j]);
                name[j+1] = name[j];
//                strcpy(name[j], tmp);
                name[j] = tmp;
            }
        }
    }
    return 0;
}

void saveOrderedNames(char *w_file, char *name[], int num_names) {
    FILE *fp;
    
    fp = fopen(w_file, "w+");
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(-1);
    }
    
    for (int i=0; i<num_names;i++) {
        if (i == num_names-1)
            fputs(name[i], fp);
        else
            fprintf(fp, "%s%c", name[i], ',');
        
        printf("%d: %s\n", i, name[i]);
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
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
    }
    else
        perror("getcwd() error");
    
    if(argc == 2){
        printf("%s\n", argv[1]);
        strcpy(r_file, cur_path);
        strcat(r_file, argv[1]);
    }
    else if(argc == 3){
        printf("%s\n", argv[1]);
        printf("%s\n", argv[2]);
        strcpy(r_file, cur_path);
        strcat(r_file, argv[1]);
        strcpy(w_file, cur_path);
        strcat(w_file, argv[2]);
    }
    
    printf("Input file is %s\n", r_file);

    fp = fopen(r_file, "r");
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(-1);
    }
    
    printf("The contents of %s file are:\n", argv[1]);
    int i = 0;
    while((ch = fgetc(fp)) != EOF) {
        if (ch != '\n') // // ignore new line char
            line[i] = ch;
        printf("%c", ch);
        i++;
    }
    fclose(fp);
    
    // get the first token
    token = strtok(line, ",");
 
    i=0;
    // get other tokens
    while( token != NULL ) {
        name[i] = token;
        token = strtok(NULL, ",");
        i++;
    }
    
    int name_size = sizeof(name)/sizeof(name[0]);

    bubbleSortNames(name, name_size);
    saveOrderedNames(w_file, name, name_size);
    printf("\nOutput file of sorted names is %s\n", w_file);

    return 0;
}

