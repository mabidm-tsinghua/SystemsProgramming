// lsReg.cpp : Defines the entry point for the console application.
//



/* Chapter 3. lsREG - Registry list command. */
/* lsREG [options] SubKey    //Subkey starts with predefined key name.
	List the key-value pairs.
	Options:
		-R	recursive
		-l  List extended information; namely, the last write time
			and the value type
lsReg.exe -l HKEY_CURRENT_USER\dcis\systemprogramming\abc

			*/


			/* This program illustrates:
					1.	Registry handles and traversal
					2.	Registry values
					3.	The similarity and differences between directory
						and registry traversal

				Note that there are no wild card file names and you specify the
				subkey, with all key-value pairs being listed. This is similar to
				ls with "SubKey\*" as the file specifier             */

				/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "stdafx.h"



int _tmain(int argc, LPTSTR argv[])
{
	
	HKEY hKey;
	LONG result;
	DWORD valueType, index;
	DWORD numSubKeys, maxSubKeyLen, numValues, maxValueNameLen, maxValueLen;
	DWORD valueNameLen, valueLen;
	FILETIME lastWriteTime;
	LPTSTR subKeyName, valueName;
	LPBYTE value;

	if (argc < 2) {
		_tprintf(_T("Usage: reg_path_add exe_path\n"));
		return 1;
	}

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"), 0, KEY_READ | KEY_WRITE, &hKey) != ERROR_SUCCESS)
		ReportError(_T("Cannot open subkey properly"), 2, TRUE);

	if (RegQueryInfoKey(hKey, NULL, NULL, NULL,   // infor abt each key
		&numSubKeys, &maxSubKeyLen, NULL, //maxSubKeyLen is char count not including \0
		&numValues, &maxValueNameLen, &maxValueLen, //maxValueLen in bytes
		NULL, &lastWriteTime) != ERROR_SUCCESS)
		ReportError(_T("Cannot query subkey information"), 3, TRUE);
	subKeyName = (LPTSTR)malloc(TSIZE * (maxSubKeyLen + 1));   /* +1 for null character */
	valueName = (LPTSTR)malloc(TSIZE * (maxValueNameLen + 1));
	value = (LPBYTE)malloc(maxValueLen);      /* size in bytes */

	_tprintf(_T("\nSubKey Count: %d, Values Count: %d\n"), numSubKeys, numValues); //by me for info


	for (index = 0; index < numValues; index++) {
		valueNameLen = maxValueNameLen + 1; /* A very common bug is to forget to set */
		valueLen = maxValueLen + 1;     /* these values; both are in/out params  */

		//enumerates values for the specified key
		result = RegEnumValue(hKey, index,
			valueName, &valueNameLen, //value name buffer and its length in characters
			NULL, &valueType,
			value, &valueLen);//value buffer and its length in bytes

		
		if (result == ERROR_SUCCESS && _tcscmp(_T("Path"), valueName) == 0) {
			//TCHAR exe[] = _T("C:\\XYZ\\bin");
			int path_size = _tcslen(argv[1]) * TSIZE + valueLen + TSIZE;
			LPTSTR new_path = (LPTSTR)malloc(path_size);
			_stprintf(new_path, _T("%s;%s"), (LPTSTR)value, argv[1]);
			if (RegSetValueEx(hKey, valueName, 0, valueType, (LPBYTE)new_path, path_size) != ERROR_SUCCESS)
				ReportException(_T("PATH update failed \n"), 1);
			_tprintf(_T("PATH updated successfully\n"));

		}
	}

	RegCloseKey(hKey);

	return 0;
}

