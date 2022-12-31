# Simpler-RPM-WPM
A simpler way to do RPM or WPM  

## Usage:  

Basic usage:
```cpp
#include "ProcessMemory.h"

...

PMem::Mem mem(
    1144,               // process id
    PROCESS_ALL_ACCESS  // desired access rights
);

int* ptr2int = 0x61fef8;

// READ
int intRead;
mem.read(
    ptr2int,            // address
    sizeof(intRead)     // size
    ) >> intRead;       // buffer

// WRITE
int intWrite = 10;
mem.write(
    ptr2int,            // address
    sizeof(intWrite)    // size
    ) << intWrite;      // buffer
```

Get success:  
```cpp
bool ret = mem.read(
    ptr2int,            // address
    sizeof(intRead)     // size
    ) >> intRead;       // buffer

// OR

if (mem.read(ptr2int, sizeof(intRead)) >> intRead) {
    // on success
}
```

Get LastError:   
```cpp
mem.read(
    ptr2int,            // address
    sizeof(intRead)     // size
    ) >> intRead;       // buffer

mem.lastError;          // last error
```

Get number of bytes written/read:   
```cpp
mem.read(
    ptr2int,            // address
    sizeof(intRead)     // size
    ) >> intRead;       // buffer

mem.numberOfBytes;      // number of bytes
```
