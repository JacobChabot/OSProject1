#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// help function to display the allowed arguments
void help() {
	printf("-i <input file name>\n");
	printf("-o <ouuput file name>\n");
}



// input file function
void inputFile(char * name) {
	// open file
	FILE * file = NULL; 
	file = fopen(name, "r");
	// check if the file was successfuly opened
	if (file == NULL) {
		fprintf(stderr, "Invalid file");
		exit(0);
	}

	// this puts the first number of the input file into firstLine to get the parameters of the for loop
	int firstLine;
	fscanf(file, "%d", &firstLine);
	printf("First line of file: %d\n", firstLine);
	
	// this keeps track what line of the file the program should currently be reading
	int lineRead = 2;

	// for loop to start forking 
	int i;
	for (i = 0; i < firstLine; i++) {
		// begin forking, if child, process file and exit
		pid_t childPid = fork();
		if (childPid == 0) {
			// variable to keep track of what the size of the next stack should be
			int temp = 0;	
			int numberArray[99];
			while (!feof(file)) {
				fscanf(file, "%d", &numberArray[temp + 1]);
			       	printf("%d", numberArray[temp + 1]);
				temp++;
			}

			// while loop to begin traversing the file
			printf("Child process. PID: %d\n", getpid());
			fclose(file);
			exit(0);
		}
		else {
			// if parent, wait for child to exit then continue loop
			wait(0);
			printf("Parent process. PID: %d\n", getpid());
		}
	}
	
	fclose(file);
}

//output file function
void outputFile(char * name) {
	printf("output file function\n");
}

// main function
int main(int argc, char** argv) {
	// default file names
	char * inputFileName = "input.dat";
	char * outputFileName = "output.dat";

	// this switch case accepts command line options and changes the input and output file names if the user
	// selected the option
	char ch;
	while((ch = getopt(argc, argv, "hi:o:")) != -1) {
		switch(ch) {
			case 'h':
				help();
				break;
			case 'i':
				inputFileName = strdup(optarg);
				continue;
			case 'o':
				outputFileName = strdup(optarg);
				continue;
			default:
				//fprintf(stderr, "Unrecogonized options\n");
				// if the user choose no options then it will use the default input.dat and output.dat file names
				break;
		}
	}

	inputFile(inputFileName);
	outputFile(outputFileName);

	return 0;
}
