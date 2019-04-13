#include <stdio.h>

int main(int argc, char *argv[]){
	// argv 1 - name of file to read in a list of names
	// argv 2 - name of file to write out the sorted list of names
	if(argc == 2){
		printf("%s\n", argv[1]);
	}
	else if(argc == 3){
		printf("%s\n", argv[1]);
		printf("%s\n", argv[2]);
	}
	
	return 0;
}