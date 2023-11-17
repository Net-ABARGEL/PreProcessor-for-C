
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE  500 // max line size

int  deleteTheNote(char*); // a function that delete the note
char * checkForNote(char*);// function that check for note
void copyToNewFile(FILE*, FILE*); // copy the .c file to .c1 file without the note
void checkTheFile(char *); // a function that check if the file is .c file
static int flag = 0; // a flag if its inside a note or not

// a function that copy the data to a new file,
// id there is a note, it will be deleted until the end of the note
void copyToNewFile(FILE  *fp, FILE *wfp)
{
	char *buf1 = malloc(sizeof(char)*MAX_LINE); // full line at the file
	if (buf1 == NULL) // check if worked
		printf("unable to allocate memory");
	while (fgets(buf1,500,fp)!=NULL) // til the end of the file
	{
			buf1 = checkForNote(buf1); // check for new note
			if (flag==1) // in a middle of note
				*(buf1+strlen(buf1)) = '\n'; // a new line
			fputs(buf1,wfp); // print the text without the note
	}
	free(buf1);
}
// a function that delete the data until we found the end of the note "*/"
int deleteTheNote(char *pointer)
{
	int i =0; // index
	while (*(pointer+i)!=NULL)
	{
		if (*(pointer+i) == '*' && *(pointer+i+1) == '/') // check for the end of the note
			{
				flag = 0; // if its the end flag it is not a note
				break; // end of note
			}
		i++;
	}
	return i+2; // returning the length of the note + 2 because the "*/"
}

// a function that check if there is note in .c file and copy the data to .c1 file without the
//notes
char * checkForNote(char *pointer)
{

	char *newPointer = malloc(sizeof(char)*MAX_LINE); // new char* to copy
	if (newPointer == NULL)
		printf("can't orgenize a memory");
	int i =0;//index
	int j=0; // index
	while (*(pointer+i)!=NULL)
	{
		if (flag==0) // not begginning of note
		{
			if (*(pointer+i)=='/'&&*(pointer+i+1)=='*') // a note
			{
				flag =1; // flage that its a middle of note
				j = i+ deleteTheNote(pointer+i); // getting the length of the note
			}
		}
		else

			if (flag==1) // in a middle of note
				j = i+ deleteTheNote(pointer+i); // delete the note and conitnue

		*(newPointer+i) = *(pointer+j); // copying the data without the nore
		i++;
		j++;
	}
	return newPointer;

}
// a function that check if there is a .c file
// if not - exit from the program;
 void checkTheFile(char *  argv)
{
	int i=strlen(argv)-1;// the last char at argv
	char *fileEnd = ".c\0";
	for (int j=1;j>-1;j--) // chekc the end of the file name
	{
		if (*(fileEnd+j)!= *(argv+i)) // not a 'c' or '.'
		{
			printf("the file is not a .c format");
			exit(0); //exit the program
		}
		i--;
	}
	printf("its a .c file name");
	return;  // its a .c file
}
