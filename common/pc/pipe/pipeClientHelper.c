#include "pipeClientHelper.h"

#include <windows.h>
#include <stdbool.h>

HANDLE initClientPipe(LPCWSTR pipeName) {
    printf("Create the Client Pipe '%ls' ... ", pipeName);
    HANDLE result = CreateFile(
        pipeName,        // pipe name 
        GENERIC_READ,    // read,
        0,              // no sharing 
        NULL,           // default security attributes
        OPEN_EXISTING,  // opens existing pipe 
        0,              // default attributes 
        NULL);          // no template file 

    if (GetLastError() != 0)
    {
        printf("KO : lastError=%d.\r\n", GetLastError());
        getchar();
        return NULL;
    }
    else {
        printf("OK !\r\n");
    }
    return result;
}

unsigned char readCharFromPipe(HANDLE pipe) {
    #define NUMBER_OF_BYTES_TO_READ 1
    unsigned char buffer[NUMBER_OF_BYTES_TO_READ + 1];
    buffer[0] = '\0';
    DWORD numBytesRead = 0;

    DWORD lpBytesReads;
    DWORD lpTotalBytesAvail;
    DWORD lpBytesLeftThisMessage;
    PeekNamedPipe(pipe, buffer, NUMBER_OF_BYTES_TO_READ, &lpBytesReads, &lpTotalBytesAvail, &lpBytesLeftThisMessage);
    if (lpTotalBytesAvail == 0) {
        return 0;
    }
 
    BOOL ok = ReadFile(
        pipe,
        buffer, // the data from the pipe will be put here
        NUMBER_OF_BYTES_TO_READ, // number of bytes allocated
        &numBytesRead, // this will store number of bytes actually read
        NULL // not using overlapped IO
        );
    unsigned char result = buffer[0];

    int lastError = GetLastError();

    if (lastError == ERROR_BROKEN_PIPE) {
        printf("The pipe Has Been Ended (%d)\r\n", lastError);
        return result;
    }
    else if (lastError != 0) {
        printf("readCharFromPipe->lastError: %d\r\n", lastError);
    }
    if (!ok) {
        printf("readCharFromPipe->Failed to read data from the pipe.\r\n");
    }
    else {
        // printf("Content of bytes read: %d\r\n", result);
    }

    return result;
}
