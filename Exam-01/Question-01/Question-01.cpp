// cpW.cpp : Sequential file copy using windows API.
//
/* Chapter 1. Basic cp file copy program. Win32 Implementation. */
/* cpW file1 file2: Copy file1 to file2. */

#include "stdafx.h"

#define BUF_SIZE 512  

int _tmain(int argc, TCHAR* argv[]) // Notice: int _tmain (int argc, LPTSTR argv [])
{
	HANDLE hIn;
	TCHAR buffer[BUF_SIZE];
	

	
	hIn = CreateFile(argv[1], GENERIC_READ|GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn == INVALID_HANDLE_VALUE) {
		ReportError(_T("\nError: File does not exist."), 1, TRUE);
	}

	_fgetts(buffer, sizeof(buffer), stdin);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		
	}

	hOut = CreateFile(argv[2], GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOut == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Cannot open output file. Error: 0X%x\n", GetLastError());
		CloseHandle(hIn);
		return 3;
	}
	while (ReadFile(hIn, buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
		WriteFile(hOut, buffer, nIn, &nOut, NULL);
		if (nIn != nOut) {
			fprintf(stderr, "Fatal write error: 0X%x\n", GetLastError());
			CloseHandle(hIn); CloseHandle(hOut);
			return 4;
		}
	}

	/*
	HANDLE hIn2 = CreateFile (argv[1], GENERIC_READ,FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn2 == INVALID_HANDLE_VALUE) {
		fprintf (stderr, "Cannot open SECOND . Error: %x\n", GetLastError ());
		return 2;
	}
	//

		HANDLE hIn3 = CreateFile (argv[1], GENERIC_READ,FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn3 == INVALID_HANDLE_VALUE) {
		fprintf (stderr, "Cannot open THird . Error: %x\n", GetLastError ());
		return 2;
	}
	*/

	CloseHandle(hIn); //invalidates the hIn, decrement the object count, check if object can be destroyed
	CloseHandle(hOut);

	return 0;
}


