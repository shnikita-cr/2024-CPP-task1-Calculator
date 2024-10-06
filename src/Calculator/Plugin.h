#ifndef TASK1_PLUGIN_H
#define TASK1_PLUGIN_H

#include <windows.h>
#include "../Operation/Operation.h"

typedef Operation *(*CreateOpFunc)();

typedef void (*DestroyOpFunc)(Operation *);

struct Plugin {
    CreateOpFunc createF;
    DestroyOpFunc destroyF;
    HMODULE hDll;
    Operation *op;

    Plugin() {
        createF = nullptr;
        destroyF = nullptr;
        hDll = nullptr;
        op = nullptr;
    }
};

#endif //TASK1_PLUGIN_H
