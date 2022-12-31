#include <windows.h>

#include <stdexcept>

namespace PMem {

class Mem {
   private:
    DWORD _pid = -1;
    HANDLE _pHandle = NULL;
    LPVOID _address = NULL;
    SIZE_T _nSize = 0;
    bool _isReadOrWrite = true;

   public:
    SIZE_T numberOfBytes = 0;
    DWORD lastError = 0;
    Mem(DWORD pid, DWORD desiredAccess) {
        _pid = pid;
        _pHandle = OpenProcess(desiredAccess, FALSE, (DWORD)pid);
        if (_pHandle == NULL) {
            throw std::runtime_error("Unable to get process handle.");
        }
    }

    template <typename TADDR>
    Mem& read(TADDR address, SIZE_T nSize) {
        _isReadOrWrite = true;
        _address = (LPVOID)address;
        _nSize = nSize;
        return *this;
    }

    template <typename TADDR>
    Mem& write(TADDR address, SIZE_T nSize) {
        _isReadOrWrite = false;
        _address = (LPVOID)address;
        _nSize = nSize;
        return *this;
    }

    BOOL operator<<(const LPVOID& buffer) {
        BOOL ret;
        if (!_isReadOrWrite) {
            ret = WriteProcessMemory(_pHandle, _address, buffer, _nSize, &numberOfBytes);
            if (!ret) lastError = GetLastError();
        } else {
            throw std::runtime_error("Not under WRITE mode.");
        }
        return ret;
    }

    BOOL operator>>(const LPVOID& buffer) {
        BOOL ret;
        if (_isReadOrWrite) {
            ret = ReadProcessMemory(_pHandle, _address, buffer, _nSize, &numberOfBytes);
            if (!ret) lastError = GetLastError();
        } else {
            throw std::runtime_error("Not under READ mode.");
        }
        return ret;
    }
};

}