#include "Utils.h"

uintptr_t Utils::evaluatePtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) { // unused
    uintptr_t addr = baseAddr;

    for (int I = 0; I < offsets.size(); I++) {
        addr = *(uintptr_t*)(addr);
        if ((uintptr_t*)(addr) == nullptr)
            return addr;
        addr += offsets[I];
    };

    return addr;
};

uintptr_t Utils::evaluateBasePtr(std::vector<unsigned int> offsets) {
    uintptr_t addr = (uintptr_t)GetModuleHandleA("sauerbraten.exe");

    for (int I = 0; I < offsets.size(); I++) {
        addr = *(uintptr_t*)(addr);
        if ((uintptr_t*)(addr) == nullptr)
            return addr;
        addr += offsets[I];
    };

    return addr;
};