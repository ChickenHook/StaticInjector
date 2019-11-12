
#include <string>
#include <unistd.h>
#include <dlfcn.h>

#include "symbolhook.h"

void *handle;

void funA() {
    printf("ERROR, THIS SHOULD NEVER APPEAR");
}

extern "C" __attribute__((used)) void *p = (void *) funA;

extern "C" void _Unwind_Resume() {
    SYMBOL_HOOK(p);
}

static void __attribute__  ((constructor (103))) hookInit() {
    handle = dlopen("libgcc_s.so.1", RTLD_LAZY);
    p = dlsym(handle, "_Unwind_Resume");
}