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
void inputFile(char * name) {
	// use fork and wait?
	printf("input file function\n");
	
	// open file and read the first number to determine how many loops are needed
	FILE * file = fopen(name, "r");
	int firstLine;
	fscanf(file, "%d", &firstLine);
	printf("First line of file: %d\n", firstLine);
	
	// is this where I set up for loop and start forking? 
	int i;
	for (i = 0; i < firstLine; i++) {
		printf("Loop\n");
	}
	
	fclose(file);
}

//output file function
void outputFile(char * name) {
	printf("output file function\n");
}

// main function
int main(int argc, char** argv) {
	printf("hello world\n");

	char * inputFileName = "input.dat";
	char * outputFileName = "output.dat";



	// this specifies what option the user selected using getopt and calls the
	// appropriate function	
	char ch;
	while((ch = getopt(argc, argv, "hi::o::")) != -1) { // need help with accepting arguments
		switch(ch) {
			case 'h':
				help();
				break;
			case 'i':
				//inputFileName = optarg;
				inputFile(inputFileName);
				continue;
			case 'o':
				//outputFileName = optarg;
				outputFile(outputFileName);
				continue;
			default:
				help();
				break;
		}
	}


	return 0;
}
