/*
 ============================================================================
 Name        : preprocessor.c

 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chapter1.h" // chapter one file include
#include "chapter2.h"// chapter two file include

#define MAX_LINE  500 // max line size

int main(int argc, char **argv) {

	checkTheFile(argv[1]); // check if the argument file is a .c file

	char *newFileName =malloc (sizeof(char)*(strlen(argv[1])+2)); // make a char as long as the name +2
	if (newFileName == NULL	) // check if worked
		printf("unable to allocate memory");

	strcpy(newFileName,argv[1]); // copy the file name
	strcat(newFileName,"1"); // add "1" to the end of the file name

	FILE *fp = fopen(argv[1],"r"); // make a file pointer to the argument file
	FILE *wfp = fopen (newFileName,"w"); // create a new file with .c1 end
	if (fp ==NULL|| wfp == NULL)// if one of the files didnt open, show a message
		printf("can't open the file");

	copyToNewFile(fp,wfp); // calling the function copyNewFile and delete the notes
	checkForInclude(wfp,newFileName); // check for includes and add it to a new file with .c2 end

	free(newFileName);
	printf("we have done");
	return EXIT_SUCCESS; // end of program
}
