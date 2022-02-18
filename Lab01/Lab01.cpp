
//Lab01

#include "stdafx.h"


/*  */
/* lab01 infile1 outfile*/



#define BUF_SIZE 256
#define ctrl_z '\x1A'

int main (int argc, char *argv [])
{
	FILE *inFile, *outFile;
	char rec[BUF_SIZE];
	size_t bytesIn, bytesOut;
	if (argc != 3) {
		fprintf (stderr, "Usage: cp file1 file2\n");
		return 1;
	}

	/* In later chapters, we'll use the more secure functions, such as fopen_s
	 * See http://msdn.microsoft.com/en-us/library/8ef0s5kh%28VS.80%29.aspx 
	 * Note that this project defines the macro _CRT_SECURE_NO_WARNINGS to avoid a warning */

	//Read string from a keyboard
	/*
	printf("Enter string: ");
	fgets ( rec, BUF_SIZE, stdin );
	
	rec[strlen(rec) - 4] = ctrl_z;
		
	
	
	
	outFile = fopen (argv[2], "w");//
	if (outFile == NULL) {
		perror (argv[2]);
		return 3;
	}
	fwrite (rec, 1, strlen(rec), outFile);
	*/
	inFile = fopen (argv[1], "r");//
	if (inFile == NULL) {
		perror (argv[1]);
		return 2;
	}

	char buf[BUF_SIZE+1];
	while ((bytesIn = fread (buf, 1, BUF_SIZE, inFile)) > 0) {
		  buf[bytesIn+1] = '\0';
		  printf("%s",buf);
	}
	/* Process the input file a record at a time. */
	/*
	while ((bytesIn = fread (rec, 1, BUF_SIZE, inFile)) > 0) {
		bytesOut = fwrite (rec, 1, bytesIn, outFile);
		if (bytesOut != bytesIn) {
			perror ("Fatal write error.");
			fclose(inFile); 
			fclose(outFile);
			return 4;
		}
	}
	*/
	fclose (inFile);
	//fclose (outFile);
	return 0;
}

