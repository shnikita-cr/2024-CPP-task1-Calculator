#define POWDLL_EXPORTS
#include "library.h"

extern "C" POWDLL_API Operation* create() {
    return new Pow();
}

extern "C" POWDLL_API void destroy(Operation* obj) {
    delete obj;
}