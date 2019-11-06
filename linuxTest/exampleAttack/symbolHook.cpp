


void funA(std::string line) {
    printf("line: %s", line.c_str());
}

extern "C" __attribute__((used)) void *p = (void *) funA;

void funB(){
    asm __volatile__ ("funB: \npop %%rbp   \njmp *%0 \npush   %%rbp\n" : : "m" (p));
}

void ftest() {
    void (*strFun)(std::string);
    strFun = (void (*)(std::string)) &funB;
    sleep(1);
    strFun("This line should be printed!\n");
}
