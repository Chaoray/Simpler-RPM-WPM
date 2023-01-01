#include <windows.h>

#include <stdexcept>

namespace PMem {

class Mem {
   private:
    DWORD _pid = -1;
    HANDLE _pHandle = NULL;
    LPVOID _address = NULL;
    SIZE_T _nSize = -1;

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

    ~Mem() {
        CloseHandle(_pHandle);
    }

    Mem& operator()(SIZE_T nSize) {
        _nSize = nSize;
    }

    template <typename TADDR>
    Mem& operator[](const TADDR& address) {
        _address = (LPVOID)address;
        return *this;
    }

    template<typename TBUFFER>
    BOOL operator<<(const TBUFFER& buffer) {
        BOOL ret;
        if (_nSize != -1) {
            ret = WriteProcessMemory(_pHandle, _address, (LPVOID)&buffer, _nSize, &numberOfBytes);
        } else {
            ret = WriteProcessMemory(_pHandle, _address, (LPVOID)&buffer, sizeof(buffer), &numberOfBytes);
        }

        if (!ret) lastError = GetLastError();
        return ret;
    }

    template<typename TBUFFER>
    BOOL operator>>(const TBUFFER& buffer) {
        BOOL ret;
        if (_nSize != -1) {
            ret = ReadProcessMemory(_pHandle, _address, (LPVOID)&buffer, _nSize, &numberOfBytes);
        } else {
            ret = ReadProcessMemory(_pHandle, _address, (LPVOID)&buffer, sizeof(buffer), &numberOfBytes);
        }
        if (!ret) lastError = GetLastError();
        return ret;
    }
};

}  // namespace PMem