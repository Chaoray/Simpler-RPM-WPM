#pragma once

#include <windows.h>
#include <psapi.h>

class MPointer {
   private:
    DWORD _pid = -1;
    HANDLE _pHandle = nullptr;
    uintptr_t _address = 0;

   public:
    uintptr_t b = 0;
    SIZE_T numberOfBytes = 0;
    DWORD lastError = 0;

    MPointer(DWORD pid, DWORD desiredAccess) {
        _pid = pid;
        _pHandle = OpenProcess(desiredAccess, FALSE, (DWORD)pid);
        base();
    }

    ~MPointer() {
        if (_pHandle != NULL) CloseHandle(_pHandle);
    }

    uintptr_t& operator+(const uintptr_t& offset) {
        _address += offset;
        return _address;
    }

    uintptr_t& operator-(const uintptr_t& offset) {
        _address -= offset;
        return _address;
    }

    MPointer& operator[](const uintptr_t& address) {
        _address = address;
        return *this;
    }

    uintptr_t base() {
        if (!_pHandle) return 0;

        HMODULE lphModule[1024];
        DWORD lpcbNeeded = 0;

        if (!EnumProcessModules(_pHandle, lphModule, sizeof(lphModule), &lpcbNeeded))
            return 0;

        TCHAR szModName[MAX_PATH];
        if (!GetModuleFileNameEx(_pHandle, lphModule[0], szModName, sizeof(szModName) / sizeof(TCHAR)))
            return 0;

        if (this->b == 0) {
            this->b = reinterpret_cast<uintptr_t>(lphModule[0]);
        }

        return reinterpret_cast<uintptr_t>(lphModule[0]);
    }

    template <typename BUFFER>
    bool write(BUFFER* buffer) {
        if (!_address) return FALSE;

        BOOL ret;
        ret = WriteProcessMemory(
            _pHandle,
            reinterpret_cast<LPVOID>(_address),
            reinterpret_cast<LPCVOID>(buffer),
            sizeof(buffer),
            &numberOfBytes);

        if (!ret) lastError = GetLastError();

        return ret;
    }

    template <typename BUFFER>
    bool read(BUFFER* buffer) {
        if (!_address) return FALSE;

        BOOL ret;
        ret = ReadProcessMemory(
            _pHandle,
            reinterpret_cast<LPCVOID>(_address),
            reinterpret_cast<LPVOID>(buffer),
            sizeof(buffer),
            &numberOfBytes);

        if (!ret) lastError = GetLastError();

        return ret;
    }
};
