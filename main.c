#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// help function to display the allowed arguments
void help() {
	printf("-i <input file name>\n");
	printf("-o <ouuput file name>\n");
}

// input file function
void inputFile() {
	printf("input file function\n");
}

//output file function
void outputFile() {
	printf("output file function\n");
}

// main function
int main(int argc, char** argv) {
	printf("hello world\n");

	// this inserts the file name if given only if the appropriate number of arguments are passed
	// this is to prevent a segmentation fault
	char * fName;
	if (argc > 2) {
		fName = strdup(argv[2]);
		printf("%s", fName);
	}
	else {
		fName = strdup("blank");
		printf("%s", fName);
	}
		
	// this specifies what option the user selected using getopt and calls the
	// appropriate function	
	int option;
	while((option = getopt(argc, argv, "hio:")) != -1) {
		switch(option) {
			case 'h':
				help();
				break;
			case 'i':
				inputFile();
				continue;
			case 'o':
				outputFile();
				continue;
			default:
				help();
				break;
		}
	}



	return 0;
}
