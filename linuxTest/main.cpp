//
// Created by Sascha Roth on 03.11.19.
//


#include <BinaryEditor.h>
#include <IBinary.h>
#include <iostream>
#include <unistd.h>
#include <dlfcn.h>
#include <asm/mman.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/stat.h>

/*extern "C" void _Unwind_Resume(){

}*/
void logCallback(const std::string &logtext) {
    std::cout << logtext << std::endl;
}

void printHelp() {
    std::cout << "ChickenHook - StaticInjector" << std::endl << "Usage:" << std::endl << std::endl
              << "  ./staticInjector [binaryToInjectInto] [dependency to replace] [path to dependency to generate the stubs]"
              << std::endl << std::endl << "ex.:" << std::endl
              << "  ./staticInjector victimTest libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1"
              << std::endl
              << "Read more at: https://github.com/ChickenHook/StaticInjector" << std::endl;
}

bool exist(const char *name) {
    struct stat buffer;
    return (stat(name, &buffer) == 0);
}

int main(int argc, char *argv[]) {
    // ./linuxTest victimTest libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
    if (argc < 4) {
        printHelp();
        return 1;
    }// TODO add nice user interface here

    if (!exist(argv[1])) {
        std::cout << "given target file <%s> does not exist" << argv[1] << std::endl;
        printHelp();
        return 1;
    }

    if (!exist(argv[3])) {
        std::cout << "given target file <%s> does not exist" << argv[1] << std::endl;
        printHelp();
        return 2;
    }
    std::cout << "Trying to parse file <" << argv[1] << ">" << std::endl;
    ChickenHook::BinaryEditor binaryEditor;
    binaryEditor.setLoggingCallback(logCallback);
    auto binary = binaryEditor.open(argv[1]);
    binary->replaceDependency(argv[2]);
    auto dependency = binaryEditor.open(argv[3]);
    if (dependency != nullptr) {
        dependency->generateSymbolHooks(argv[2], (std::string(argv[2]) + ".cpp").c_str());
    }

    //binary->addLibraryDependency(argv[2]);

    return 0;
}
