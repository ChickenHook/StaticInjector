
#include <string>
#include <unistd.h>
#include <dlfcn.h>

#ifdef __x86_64__
#define SYMBOL_HOOK(a) asm __volatile__ ("funB: \npop %%rbp   \njmp *%0 \npush   %%rbp\n" : : "m" (a))
#else
#error "UNSUPPORTED ARCHITECTURE"
#endif

void *handle;

void funA() {
    printf("ERROR, THIS SHOULD NEVER APPEAR");
}

extern "C" __attribute__((used)) void *p = (void *) funA;

extern "C" void _Unwind_Resume() {
    SYMBOL_HOOK(p);
}

void __attribute__  ((constructor (103))) symbolHookInit() {
    handle = dlopen("libgcc_s.so.1", RTLD_LAZY);
    p = dlsym(handle,"_Unwind_Resume");
}