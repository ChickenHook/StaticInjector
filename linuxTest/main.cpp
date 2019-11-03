//
// Created by Sascha Roth on 03.11.19.
//


#include <BinaryEditor.h>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please specify injection path" << std::endl;
        return 1;
    }// TODO add nice user interface here

    std::cout << "Trying to parse file <" << argv[1] << ">" << std::endl;
    ChickenHook::BinaryEditor binaryEditor;
    binaryEditor.open(argv[1]);
    return 0;
}
