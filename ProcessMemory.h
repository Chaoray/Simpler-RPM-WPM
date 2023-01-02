#include <windows.h>

#include <stdexcept>
#include <type_traits>

class MPointer {
   private:
    DWORD _pid = -1;
    HANDLE _pHandle = NULL;
    uintptr_t _address = (uintptr_t)nullptr;
    SIZE_T _nSize = -1;

   public:
    SIZE_T numberOfBytes = 0;
    DWORD lastError = 0;
    MPointer(DWORD pid, DWORD desiredAccess) {
        _pid = pid;
        _pHandle = OpenProcess(desiredAccess, FALSE, (DWORD)pid);
        if (_pHandle == NULL) {
            throw std::runtime_error("Unable to get process handle.");
        }
    }

    ~MPointer() {
        if(_pHandle != NULL) CloseHandle(_pHandle);
    }

    MPointer& operator()(SIZE_T nSize) {
        _nSize = nSize;
        return *this;
    }

    uintptr_t& operator+(const int& offset) {
        _address += offset;
        return _address;
    }

    uintptr_t& operator-(const int& offset) {
        _address -= offset;
        return _address;
    }

    uintptr_t& operator++() {
        _address++;
        return _address;
    }

    uintptr_t& operator--() {
        _address--;
        return _address;
    }

    MPointer& operator=(uintptr_t& address) {
        _address = address;
        return *this;
    }

    template<typename TADDR>
    MPointer& operator[](const TADDR& address) {
        _address = (uintptr_t)address;
        return *this;
    }

    BYTE* operator!() {
        if (!_address) return NULL;

        BYTE* buffer = new BYTE[_nSize];
        BOOL ret;
        ret = ReadProcessMemory(_pHandle, (LPCVOID)_address, &buffer, _nSize, &numberOfBytes);
        if (!ret) lastError = GetLastError();

        return buffer;
    }

    template<typename TBUFFER>
    BOOL operator<<(const TBUFFER& buffer) {
        if (!_address) return FALSE;
        BOOL ret;
        if (_nSize != -1) {
            ret = WriteProcessMemory(_pHandle, (LPVOID)_address, (LPCVOID)buffer, _nSize, &numberOfBytes);
        } else {
            ret = WriteProcessMemory(_pHandle, (LPVOID)_address, (LPCVOID)buffer, sizeof(buffer), &numberOfBytes);
        }

        if (!ret) lastError = GetLastError();
        return ret;
    }

    template<typename TBUFFER>
    BOOL operator>>(const TBUFFER& buffer) {
        if (!_address) return FALSE;
        BOOL ret;
        if (_nSize != -1) {
            ret = ReadProcessMemory(_pHandle, (LPCVOID)_address, (LPVOID)buffer, _nSize, &numberOfBytes);
        } else {
            ret = ReadProcessMemory(_pHandle, (LPCVOID)_address, (LPVOID)buffer, sizeof(buffer), &numberOfBytes);
        }
        if (!ret) lastError = GetLastError();
        return ret;
    }
};
