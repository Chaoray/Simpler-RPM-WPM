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

...

PMem::Mem mem(
    1144,               // process id
    PROCESS_ALL_ACCESS  // desired access rights
);

int* ptr2int = 0x61fef8;
int intToWrite = 20000;
int intToRead;

// Set Address
mem[ptr2int];

// Set nSize
mem(sizeof(intToRead));

// Read
mem >> intToRead;

// Write
mem << intToWrite;
```

Get success:  
```cpp
bool ret = mem >> intRead

// OR

if (mem >> intRead) {
    // on success
}
```

Get LastError:   
```cpp
mem.lastError;          // last error
```

Get number of bytes written/read:   
```cpp
mem.numberOfBytes;      // number of bytes
```
