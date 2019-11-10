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

/*extern "C" void _Unwind_Resume(){

}*/
void logCallback(const std::string &logtext) {
    std::cout << logtext << std::endl;
}

int main(int argc, char *argv[]) {

    if (argc < 4) {
        std::cout << "Please specify injection path" << std::endl;
        return 1;
    }// TODO add nice user interface here

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
