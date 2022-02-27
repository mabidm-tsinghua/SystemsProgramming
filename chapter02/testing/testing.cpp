// testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

VOID ReportError (LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage);



#include <stdlib.h>

int _tmain (int argc, LPCTSTR *argv)
{   
	
	char i = -1 % 256;
	
	printf("%hhu \n", i);
	
	
  return 0;
}



VOID ReportError (LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage)

/* General-purpose function for reporting system errors.
	Obtain the error number and convert it to the system error message.
	Display this information and the user-specified message to the standard error device.
	userMessage:		Message to be displayed to standard error device.
	exitCode:		0 - Return.
					> 0 - ExitProcess with this code.
	printErrorMessage:	Display the last system error message if this flag is set. */
{
	DWORD eMsgLen, errNum = GetLastError ();
	LPTSTR lpvSysMsg=NULL;
	_ftprintf (stderr, _T("%s\n"), userMessage);
	int a=12;
	
	if (printErrorMessage) {
		eMsgLen = FormatMessage (FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
				_T(" Cannot NULL %1!d!"), errNum, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpvSysMsg, 0, (va_list*)&a);
		if (eMsgLen > 0)
		{
			_ftprintf (stderr, _T("%s\n"), lpvSysMsg);
		}
		else
		{
			_ftprintf (stderr, _T("Last Error Number; %d.\n"), errNum);
		}

		if (lpvSysMsg != NULL) LocalFree (lpvSysMsg); /* Explained in Chapter 5. */
	}

	if (exitCode > 0)
		ExitProcess (exitCode);

	return;
}