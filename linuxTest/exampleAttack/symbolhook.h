#pragma once

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

#ifdef __x86_64__
#define SYMBOL_HOOK(a) asm __volatile__ ("pop %%rbp   \njmp *%0 \npush   %%rbp\n" : : "m" (a))
#else
#error "UNSUPPORTED ARCHITECTURE"
#endif