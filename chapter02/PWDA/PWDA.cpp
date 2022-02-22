// PWDA.cpp : Defines the entry point for the console application.
//

/* Chapter 2. pwda. */
/* pwd: Similar to the UNIX command. */
/* This program illustrates:
		1. Win32 GetCurrentDirectory
		2. Testing the length of a returned string
		3. A Version - allocate enough memory for the path */

#include "stdafx.h"
#include <stdlib.h>



VOID ReportError (LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage);

int _tmain (int argc, LPTSTR argv [])
{
	/* Buffer to receive current directory allows
		for longest possible path. */

	DWORD LenCurDir = GetCurrentDirectory (0, NULL);
	/* Return length allows for terminating null character
		 */
	LPTSTR pwdBuffer = (LPTSTR) malloc (LenCurDir * sizeof (TCHAR));

	if (pwdBuffer == NULL)
		ReportError (_T ("Failure allocating pathname buffer."), 1, TRUE);

	LenCurDir = GetCurrentDirectory (LenCurDir, pwdBuffer);
	
	_ftprintf (stderr, _T("%s\n"), pwdBuffer);

	free (pwdBuffer);
	return 0;
}


