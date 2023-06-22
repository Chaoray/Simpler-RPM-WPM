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

// Read
mptr.read<int>(&intToRead);

// Write
mptr.write<int>(&intToWrite);
```

Some combinations:
```cpp
int intToRead;
mptr[ptr2int].read<int>(&intToRead);
```

Operators:  
```cpp
// the followings will return the address after calculating
mptr + 0x98;
mptr - 0x98;
```

Get success:  
```cpp
bool ret = mptr.read<int>(&intRead);

// OR

if (mptr.read<int>(&intRead)) {
    // on success
}
```

Public Members:   
```cpp
mptr.lastError;          // last error
mptr.numberOfBytes;      // number of bytes
mptr.b;                  // base address of the process
mptr.base();             // get base address of the process
```
