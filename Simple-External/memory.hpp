#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

namespace memory {
    inline HANDLE handle = nullptr;
    inline DWORD pid = 0;

    bool attach(const std::wstring& proc_name) {
        PROCESSENTRY32 entry = { sizeof(PROCESSENTRY32) };
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (snapshot == INVALID_HANDLE_VALUE) return false;

        while (Process32Next(snapshot, &entry)) {
            if (proc_name == entry.szExeFile) {
                pid = entry.th32ProcessID;
                handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
                CloseHandle(snapshot);
                return handle != nullptr;
            }
        }

        CloseHandle(snapshot);
        return false;
    }

    template<typename T>
    T read(uintptr_t addr) {
        T buffer{};
        ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(addr), &buffer, sizeof(T), nullptr);
        return buffer;
    }

    template<typename T>
    void write(uintptr_t addr, T value) {
        WriteProcessMemory(handle, reinterpret_cast<LPVOID>(addr), &value, sizeof(T), nullptr);
    }

    std::string read_string(uintptr_t addr, size_t max = 200) {
        std::string str;
        for (size_t i = 0; i < max; i++) {
            char ch;
            ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(addr + i), &ch, 1, nullptr);
            if (ch == '\0') break;
            str += ch;
        }
        return str;
    }

    uintptr_t get_module_base(const std::wstring& mod_name) {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        MODULEENTRY32 modEntry = { sizeof(MODULEENTRY32) };
        uintptr_t base = 0;

        if (snapshot == INVALID_HANDLE_VALUE) return 0;

        while (Module32Next(snapshot, &modEntry)) {
            if (mod_name == modEntry.szModule) {
                base = reinterpret_cast<uintptr_t>(modEntry.modBaseAddr);
                break;
            }
        }

        CloseHandle(snapshot);
        return base;
    }
}