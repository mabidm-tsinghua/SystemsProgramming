/******************************************************************************
Module:  MMFShare.cpp
Notices: Copyright (c) 2008 Jeffrey Richter & Christophe Nasarre
******************************************************************************/


#include "stdafx.h"
void OnCommand(int command);

///////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, LPTSTR argv[]) {
    int command = 4;
    _tprintf(_T("\n\t 1 to create file mapping object." \
                                "\n\t 2 to close file mapping object." \
                                "\n\t 3 to Read shared data " \
                                "\n\t 4 to return "));
    _tprintf(_T("\nEnter command: "));
    _tscanf(_T("%d"),&command);
    /*  Call the function. */
    
    while (TRUE) __try{
        if (command == 4) { return 2;}
        OnCommand(command);
        _tprintf(_T("\nEnter command: "));
        _tscanf(_T("%d"), &command);
    }__except (EXCEPTION_EXECUTE_HANDLER) {
        _tprintf(_T("\nException Generated: "));
        _tprintf(_T("\nEnter command: "));
        _tscanf(_T("%d"), &command);
    }

    
    return 0;
}



///////////////////////////////////////////////////////////////////////////////


void OnCommand(int command) {

    // Handle of the open memory-mapped file
    static HANDLE s_hFileMap = NULL;

    switch (command) {
    
    case 1:
        
        // Create a paging file-backed MMF to contain the edit control text.
        // The MMF is 4 KB at most and is named MMFSharedData.
        s_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
            PAGE_READWRITE, 0, 4 * 1024, TEXT("MMFSharedData"));

        if (s_hFileMap != NULL) {

            if (GetLastError() == ERROR_ALREADY_EXISTS) {
                _tprintf(_T("Mapping already exists - not created."));
                CloseHandle(s_hFileMap);

            }
            else {

               // File mapping created successfully.

                // Map a view of the file into the address space.
                LPTSTR pView = (LPTSTR)MapViewOfFile(s_hFileMap,
                    FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

                if (pView != NULL) {
                    // Put text into the MMF.
                    _stprintf(pView, _T("%s"), _T("Writing Data to MMFSharedData"));
                    _tprintf(_T("Data Written\n"));
                    // Protect the MMF storage by unmapping it.
                    UnmapViewOfFile(pView);
                }
                else {
                    ReportException(_T("Can't map view of file."),1);
                }
            }

        }
        else {
            ReportException(_T("Can't create file mapping."),1);
        }
        break;

    case 2:
        
        if (CloseHandle(s_hFileMap)) { _tprintf(_T("File mapping object closed \n")); };
        break;

    case 3:
        
        // See if a memory-mapped file named MMF SharedData already exists.
        HANDLE hFileMapT = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
            FALSE, TEXT("MMFSharedData"));

        if (hFileMapT != NULL) {
            // The MMF does exist, map it into the process's address space.
            LPTSTR pView = (LPTSTR)MapViewOfFile(hFileMapT,
                FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

            if (pView != NULL) {

                // Put the contents of the MMF into the edit control.
                _tprintf(_T(" Reading Data: %s\n"),pView);
                UnmapViewOfFile(pView);
            }
            else {
                ReportException(_T("Can't map view of file."), 1);
            }

            CloseHandle(hFileMapT);

        }
        else {
            ReportException(_T("Can't Open file mapping."), 1);
        }
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////

//////////////////////////////// End of File //////////////////////////////////
