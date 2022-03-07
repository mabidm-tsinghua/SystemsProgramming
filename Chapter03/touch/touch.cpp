// touch.cpp : Defines the entry point for the console application.
//

/* Chapter 3. touch command. */
/* Modified Sept 2, 2005 to fix the -a and -m logic 
     Modified again Jan 4, 2016 - the 2005 change was too complex.*/
/* touch[options] file1 file2 file3 ...
	Update the access and modification times of the files.
	Create non-existent files.
	Options:
		-a Only update the access time.
		-m update the modification (last write) time and access time
		         
		-c Do not create a non-existent file. */

/* This program illustrates:
	1. Setting the file time attributes.
	2. Converting from system to file time. */

#include "stdafx.h"

int _tmain (int argc, LPTSTR argv[])
{
	FILETIME newFileTime;
	LPFILETIME pAccessTime = NULL, pModifyTime = NULL;
	HANDLE hFile;
	BOOL setAccessTime, setModTime, notCreateNew;
	DWORD CreateFlag;
	int i, FileIndex;

	/* Determine the options. */

	if (argc < 2) {
		_tprintf(_T("Usage: touch[options] files"));
		return 1;
	}
	FileIndex = Options(argc, (LPCTSTR*) argv, _T ("amc"),
			&setAccessTime, &setModTime, &notCreateNew, NULL);

	CreateFlag = notCreateNew ? OPEN_EXISTING : OPEN_ALWAYS;

	for (i = FileIndex; i < argc; i++) {
		hFile = CreateFile(argv[i], GENERIC_READ | GENERIC_WRITE, 0, NULL,
				CreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			if (!notCreateNew) ReportError (_T ("touch error: Cannot open file."), 0, TRUE);//existing file opening error
			continue;
		}
		/* Get current system time and convert to a file time.
			Do not change the create time. */
		GetSystemTimeAsFileTime(&newFileTime);
		if (setAccessTime) pAccessTime = &newFileTime;
		if (setModTime) {pModifyTime = &newFileTime;pAccessTime = &newFileTime;}
		if (!SetFileTime(hFile, NULL, pAccessTime, pModifyTime))
			ReportError(_T ("Failure setting file times."), 2, TRUE);
	
		//read file times to verify
		FILETIME fModifyTime,fAccessTime,flocalFileTime;
		if (!GetFileTime(hFile, NULL, &fAccessTime, &fModifyTime))
			ReportError(_T ("Failure getting file times."), 2, TRUE);
		
		//print file times in UTC
		SYSTEMTIME sModifyTime, sAccessTime; 
		FileTimeToSystemTime(&fModifyTime, &sModifyTime);
		_tprintf(_T("ModifyTime in UTC	%02d/%02d/%04d %02d:%02d:%02d"),
				sModifyTime.wDay, sModifyTime.wMonth, 
				sModifyTime.wYear, sModifyTime.wHour,
				sModifyTime.wMinute, sModifyTime.wSecond);
		
		//print file times in local time
		FileTimeToLocalFileTime(&fModifyTime, &flocalFileTime);
		FileTimeToSystemTime(&flocalFileTime, &sModifyTime);//for printing
		_tprintf(_T("\nModifyTime in Local	%02d/%02d/%04d %02d:%02d:%02d"),
				sModifyTime.wDay, sModifyTime.wMonth, 
				sModifyTime.wYear, sModifyTime.wHour,
				sModifyTime.wMinute, sModifyTime.wSecond);
		
		
	     //if we modify write time then access time also changes; tocuh -m filename
		FileTimeToSystemTime(&fAccessTime, &sAccessTime);
		_tprintf(_T("\nAccessTime in UTC %02d/%02d/%04d %02d:%02d:%02d"),
				sAccessTime.wDay, sAccessTime.wMonth, 
				sAccessTime.wYear, sAccessTime.wHour,
				sAccessTime.wMinute, sAccessTime.wSecond);
		
		
		CloseHandle(hFile);


		
	}
	return 0;
}


