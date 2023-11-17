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

// a function that get char* with the include line and check
 //wich file is include and return it
char * whatIsInclude(char * buf1)
{
	int i=0,j=0; //indexes
	char * buf2 = malloc (sizeof(char)*MAX_LINE);// char* for check the file name
	if (buf2 == NULL) // check if worked
		printf("unable to allocate memory");
	while (*(buf1+i)!='"') // check until get to the first "
		i++;
	i++;
	strcpy(buf2,buf1+i); // copy the rest of the line after "
	while (*(buf1+i+j)!='"') // check until get the next "
		j++;
	*(buf2+j) = '\0'; // add end of char * to the end of the include file name
	includeLength = i+j; // add the length to know how long we need to jump at the line
	return buf2; // return the include file name

}

// main chapter 2 function that check the .c1 file
// see if there is an include command
// if so it will add the include to .c2 file and the rest of the .c1 file
void checkForInclude(FILE *fp, char *fileName)
{
	fclose(fp);
	int index = 0, isInclude=0; // index and true or false integer
	FILE *fp1 = fopen(fileName,"r"); // the .c1 file
	if (fp1 == NULL)
		printf("cant open the file");
	FILE *incFile; // a new file (.c2)
	char *buf1 = malloc (sizeof(char)*MAX_LINE); // full line
	char *buf2 = malloc (sizeof(char)*MAX_LINE); // a copy of the line from the index
	char *includeFile = malloc (sizeof(char)*MAX_LINE); // the includeFIle name
	if (buf1 == NULL||buf2==NULL||includeFile==NULL) // check if worked
		printf("unable to allocate memory");

	char *newFileName; // the new file name (.c2)

	char *ch = malloc (sizeof(char)*2); // a char to add to the new file
	if (ch == NULL) // check if worked
		printf("unable to allocate memory");
	ch[1]='\0';

	strcpy(newFileName,fileName); // copy the name to new file
	newFileName[strlen(newFileName)-1] = '2';// change the end of the file to .c2


	FILE *wIfile = fopen(newFileName,"w"); // make a new file
	if (wIfile == NULL)
			printf("cant open the file");


	while (fgets(buf1,500,fp1)!=NULL) // going thro the .c1 file to check include
	{
		index=0; // index
		while (*(buf1+index)!=NULL) // checking the full line if there is #include
		{
			ch[0] = buf1[index]; // copy the char to check it

			if (ch[0]!='#') // check if its not #, if so, it will copy the char to c.2
				fputs(ch,wIfile);

			else // if its # char, it will check if its include
			{
				strcpy(buf2,buf1+index); // copy the rest f the line
				isInclude = checkInclude(buf2); // call the function that check if its influde
			}

			if (isInclude ==1) // if its really include
			{
				includeFile = whatIsInclude(buf2); // give the include file name to includeFile
				incFile = openTheFile(incFile,includeFile); // openning a new file with the include name
				if (incFile == NULL) // if an error show a message
					printf("cant open the file");
				addTheInclude(incFile,wIfile); // a function that add all the include file to .c2 file
				index = index + includeLength; // skip the #include ...."..." line
				isInclude = 0; // end of include
				fclose(incFile); // close the include file
			}
			else 
				fputs(ch,wIfile);
			index++; // gettint to the next index
		} // done to add al the line
	}// done to add all the include file

	free(buf1); // done with memory aloocation
	free(buf2);// done with memory aloocation
	free(includeFile);//done with memory aloocation
}
// a function that help to open a file
FILE * openTheFile(FILE *fp,char* fileName)
{
	fp = fopen(fileName,"r"); // open a file to read;
	return fp;// return the file

}
// a function that copy all the file data to where the include
// was writen
void addTheInclude(FILE *fp, FILE *wIfile)
{
	char *buf1 = malloc (sizeof(char)*MAX_LINE); // full line
	if (buf1 == NULL) // check if worked
		printf("unable to allocate memory");
	while (fgets(buf1,500,fp)!=NULL) // until the end of the file
		fputs(buf1,wIfile); // insert the data to the new file
	free (buf1); /// done with memory aloocation

}

// a function that check if the chat is "include"
int checkInclude(char * buf1)
{
	char *buf2 = "include"; // a char* to check if equal
	*buf1++; // because it start with #
	for (int i =0; i<7;i++) // as long as include
	{
		if (*(buf1+i)!=*(buf2+i)) // not the same
			return 0; // not enclude
	}
	free(buf2); /// done with memory aloocation
	return 1; // there is an include
}

