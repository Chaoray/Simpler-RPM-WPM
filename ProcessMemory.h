#include <windows.h>

#include <stdexcept>

class MPointer {
   private:
    DWORD _pid = -1;
    HANDLE _pHandle = NULL;
    char* _address = NULL;
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

    char*& operator+(const int& offset) {
        _address += offset;
        return _address;
    }

    char*& operator-(const int& offset) {
        _address -= offset;
        return _address;
    }

    char*& operator++() {
        _address++;
        return _address;
    }

    char*& operator--() {
        _address--;
        return _address;
    }

    MPointer& operator=(char*& address) {
        _address = address;
        return *this;
    }

    template<typename TADDR>
    MPointer& operator[](const TADDR& address) {
        _address = (char*)address;
        return *this;
    }

    BYTE* operator!() {
        if (_address == NULL) return NULL;

        BYTE* buffer = new BYTE[_nSize];
        BOOL ret;
        ret = ReadProcessMemory(_pHandle, _address, &buffer, _nSize, &numberOfBytes);
        if (!ret) lastError = GetLastError();

        return buffer;
    }

    template<typename TBUFFER>
    BOOL operator<<(const TBUFFER& buffer) {
        if (_address == NULL) return FALSE;
        BOOL ret;
        if (_nSize != -1) {
            ret = WriteProcessMemory(_pHandle, _address, (LPCVOID)buffer, _nSize, &numberOfBytes);
        } else {
            ret = WriteProcessMemory(_pHandle, _address, (LPCVOID)buffer, sizeof(buffer), &numberOfBytes);
        }

        if (!ret) lastError = GetLastError();
        return ret;
    }

    template<typename TBUFFER>
    BOOL operator>>(const TBUFFER& buffer) {
        if (_address == NULL) return FALSE;
        BOOL ret;
        if (_nSize != -1) {
            ret = ReadProcessMemory(_pHandle, _address, (LPVOID)buffer, _nSize, &numberOfBytes);
        } else {
            ret = ReadProcessMemory(_pHandle, _address, (LPVOID)buffer, sizeof(buffer), &numberOfBytes);
        }
        if (!ret) lastError = GetLastError();
        return ret;
    }
};
