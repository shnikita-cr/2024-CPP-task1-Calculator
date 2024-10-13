#define LOG10DLL_EXPORTS

#include "library.h"


extern "C" LOG10DLL_API Operation * create() {
    return new Sin();
}

extern "C" LOG10DLL_API void destroy(Operation * obj) {
    delete obj;
}