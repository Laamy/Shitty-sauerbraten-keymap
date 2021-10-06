#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <MinHook.h>
#include <cstdint>
#include <map>
#include <string>
#include <thread>

#include "Memory/Utils.h"

std::map<uint64_t, bool> keymap = std::map<uint64_t, bool>();

void init(HMODULE c) {
    if (MH_Initialize() == MH_OK) // 
    {
        std::thread([]() { // List keys in keymap correctly (Wont work for UWP programs!)
            while (true) {
                for (int i = 0; i < 0xFF; ++i) {
                    keymap[i] = GetAsyncKeyState(i);
                }
            }
        });

        //uintptr_t keymapAddr = (uintptr_t)(baseAddr + 0x1A0A6F); // keymap

        //if (MH_CreateHook((void*)keymapAddr, &keyCallback, reinterpret_cast<LPVOID*>(&_key)) == MH_OK) {
        //    MH_EnableHook((void*)keymapAddr);
        //};
    }
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hModule, 0, 0);
            break;
    }
    return TRUE;
}

