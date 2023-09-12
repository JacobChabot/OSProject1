#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// default file names
char * inputFileName = "input.dat";
char * outputFileName = "output.dat";

// help function to display the allowed arguments
void help() {
	printf("-i <input file name>\n");
	printf("-o <ouuput file name>\n");
}

// process the input file function
void processFile() {
	// open input file
	FILE * file = NULL; 
	file = fopen(inputFileName, "r");
	// check if the file was successfuly opened
	if (file == NULL) {
		fprintf(stderr, "Invalid input file name");
		exit(0);
	}
	
	// initialize int array, loop through the file, put the numbers in the array and close the file
	int numbers[100];
        int count = 0;	
        while (fscanf(file, "%d", &numbers[count]) != EOF) {
        	count++;
              }
	numbers[count] = '\0';
	fclose(file);

	// open the output file
	file = fopen(outputFileName, "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file.");
		exit(0);
	}

	// this keeps track what position of the array the program should be starting from
	// at the beginning it is set to the 2nd position in the array
	int read = 1;

	// this initializes an array of the total number set of numbers to store the child PIDs
	long int childTotal[numbers[0]];

	// for loop to start forking 
	int i;
	for (i = 0; i < numbers[0]; i++) { 
		
		// read the number that says how many numbers will follow it
		// need the counter variable to initialize the stack
		int counter = numbers[read];

		int length = 0;
		
		// begin forking, if child, process numbers, write to file and exit
		pid_t childPid = fork();
		if (childPid == 0) {
			childPid = getpid();
			// initialize the stack
			// first in last out
			int stack[counter];

			// insert the contents of the array into the stack
			for (count = 0; count < counter; count++) {
				stack[count] = numbers[read + 1 + count];
			}
			
			length = sizeof(stack)/sizeof(stack[0]);
			
			// write PID and numbers to output file
			fprintf(file, "%d: ", getpid());
			for (count = 0; count != length; length--) {
				fprintf(file, "%d ", stack[length - 1]);
			}
			fprintf(file, "\n");

			fclose(file);
			exit(0);
		}
		else {
			// if parent, wait for child to exit then continue loop
			wait(0);
		}
		
		// assign children's PID to the array
		childTotal[i] = childPid;
			
		if (i + 1 == numbers[0]) {
			fprintf(file, "All children were: ");
			length = sizeof(childTotal)/sizeof(childTotal[0]);
			for (count = 0; count < length; count++) {
                                 fprintf(file, "%ld ", childTotal[0]);
                        }
			fprintf(file, "\n");
			fprintf(file, "Parent PID: %d\n", getpid());
		}



		read = read + counter + 1;

		
	}

	

	fclose(file);
}


// main function
int main(int argc, char** argv) {
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

	processFile();

	return 0;
}
