#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE  500 // max line size
int checkInclude (char*); // a function that check
FILE * openTheFile(FILE *,char*);// a function that help to open a file
char * whatIsInclude(char *);
void checkForInclude(FILE*, char*);// A function that check for include and add the include file to .c2 file
void addTheInclude(FILE *, FILE *); // a function that copy the data inside the include file to .c2 file
static int includeLength =0; // the size to skip the include line
