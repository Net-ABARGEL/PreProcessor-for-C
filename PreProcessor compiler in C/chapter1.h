
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE  500 // max line size

int  deleteTheNote(char*); // a function that delete the note
char * checkForNote(char*);// function that check for note
void copyToNewFile(FILE*, FILE*); // copy the .c file to .c1 file withput the note
void checkTheFile(char *); // a function that check if the file is .c file
static int flag = 0; // a flag if its inside a note or not
