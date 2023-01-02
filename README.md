# Simpler-RPM-WPM
A simpler way to do RPM or WPM  

Before:
```cpp
HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 1144);
SIZE_T NumberOfBytesRead;
ReadProcessMemory(
    hProcess,
    (LPCVOID)ptr2int,
    &intRead,
    sizeof(intRead),
    &NumberOfBytesRead
);
```

## Usage  

Basic usage:
```cpp
#include "ProcessMemory.h"

MPointer mptr(
    1144,               // process id
    PROCESS_ALL_ACCESS  // desired access rights
);

int* ptr2int = 0x61fef8;
int intToWrite = 20000;
int intToRead;

// Set Address
mptr[ptr2int];

// Set nSize
mptr(sizeof(intToRead));
mptr(-1); // Auto size

// Read
mptr >> &intToRead;

// Write
mptr << &intToWrite;
```

You can do some combinations:
```cpp
int intToRead;
mptr[ptr2int](sizeof(intToRead)) >> &intToRead;

// Anything you want
mptr[0x61fef8 + 0x21][ptr2int](-1)(sizeof(intToRead)) >> &intToRead;
```

Operators:  
```cpp
mptr = (char*)0x61fef8;  // the same as mptr[0x61fef8], but safer

// the followings will return the address after calculating
mptr + 0x98;
mptr - 0x98;

mptr++;
mptr--;
```

Get success:  
```cpp
bool ret = mem >> &intRead

// OR

if (mem >> &intRead) {
    // on success
}
```

Public Members:   
```cpp
mem.lastError;          // last error
mem.numberOfBytes;      // number of bytes
```

This is totally illegal, in my opinion.  
Not recommended to use.
```cpp
!mptr;  // Read the address with nSize we set
        // After that, return the pointer(BYTE*) of the copy of the target memory 

// Example:
mptr[ptr2int];
int myInt = *((int*)!mptr);
```
