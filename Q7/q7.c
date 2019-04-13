#include <stdio.h>

int main(int argc, char *argv[]){
	// argv 1 - name of file to read in text
	// argv 2 - name of file to read in list of words to redact
	// argv 3 - name of file to write out the redacted text
	if(argc == 3){
		printf("%s\n", argv[1]);
		printf("%s\n", argv[2]);
	}
	else if(argc == 4){
		printf("%s\n", argv[1]);
		printf("%s\n", argv[2]);
		printf("%s\n", argv[3]);
	}
	
	return 0;
}