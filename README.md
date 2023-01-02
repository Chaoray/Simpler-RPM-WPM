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

Operators:  
```cpp
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
And it is not recommended to use.
```cpp
!mptr;  // Read the address with nSize we set
        // And return the pointer(BYTE*) of the copy of the target memory 

// Example:
mptr[ptr2int];
int myInt = *((int*)!mptr);
```
