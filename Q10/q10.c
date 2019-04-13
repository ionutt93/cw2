#include <stdio.h>

int main(int argc, char *argv[]){
	// argv 1 - name of file to read in the text
	// argv 2 - name of file to write out the compressed text
	if(argc == 2){
		printf("%s\n", argv[1]);
	}
	else if(argc == 3){
		printf("%s\n", argv[1]);
		printf("%s\n", argv[2]);
	}
	
	return 0;
}