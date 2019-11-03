//
// Created by Sascha Roth on 03.11.19.
//

#include "Elf.h"
#include "tools/HexDump.h"
#include <iostream>
#include <utility>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <elf.h>

constexpr uint8_t ELF_MAGIC[]{
        0x7f,
        0x45,
        0x4c,
        0x46
};

namespace ChickenHook {
    bool Elf::isElf(std::vector<uint8_t> &magic) {
        if (magic.empty()) {
            printf("Magic array empty\n");
            return false;
        }
        if (magic.size() < sizeof(ELF_MAGIC)) {
            printf("Magic array size to small\n");
            return false;
        }
        HexDump::hex_dump(&magic[0], magic.size(), std::cout);

        int i = 0;
        for (auto b:ELF_MAGIC) {
            if (b != magic[i]) {
                printf("Magic doesn't match elf (%d) <%x> : <%x>\n", i, b, magic[i]);
                return false;
            }
            i++;
        }
        printf("Found elf file\n");
        return true;
    }

    bool Elf::open() {
        _is.open(_path, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
        if (_is.good()) {
            std::ifstream::pos_type pos = _is.tellg();
            auto length = static_cast<unsigned int>(pos);
            _data.resize(length);
            _is.seekg(0, std::ios::beg);
            _is.read(reinterpret_cast<char *>(&_data[0]), length);
            decideArchitecture();
            return true;
        }
        return false;
    }

    bool Elf::close() {
        _is.close();
        return true;
    }

    Elf::Elf(std::string path) : IBinary(path), _is(), _path(std::move(path)) {
    }

    std::unique_ptr<IArchitecture> Elf::decideArchitecture() {

        switch (_data[EI_DATA]) {
            case ELFDATA2LSB:
                printf("2's complement, little endian\n");
                break;
            case ELFDATA2MSB:
                printf("2's complement, big endian\n");
                break;
            default:
                printf("INVALID endian format\n"); // TODO exception
                break;
        }

        // ABI
        switch (_data[EI_OSABI]) {
            case ELFOSABI_SYSV:
                printf("UNIX System V ABI\n");
                break;
            case ELFOSABI_LINUX:
                printf("Linux\n");
                break;
            case ELFOSABI_ARM_AEABI:
                printf("ARM EABI\n");
                break;

            default:
                printf("Unsupported abi <%d>\n", _data[EI_OSABI]);
                break;
        }

        bool is64=false;
        switch (_data[EI_CLASS]) {
            case ELFCLASS64:
                // x86_64
                printf("Elf architecture: 64 bit\n");
                is64=true;
                break;
            case ELFCLASS32:
                //x86
                printf("Elf architecture: 32 bit\n");
                break;
            default:
                printf("UNKNOWN ARCHITECTURE\n");
                break;
        }
        if(is64){

            Elf64_Ehdr *header = (Elf64_Ehdr *) &_data[0];
            switch (header->e_machine){
                case EM_NONE:
                    printf("None (0x0)\n");
                    break;

                case EM_386:
                    printf("INTEL x86 (0x%x)\n", EM_386);
                    break;

                case EM_X86_64:
                    printf("AMD x86_64 (0x%x)\n", EM_X86_64);
                    break;

                case EM_AARCH64:
                    printf("AARCH64 (0x%x)\n", EM_AARCH64);
                    break;

                case EM_ARM:
                    printf("ARM (0x%x)\n", EM_ARM);
                    break;
                default:
                    printf(" 0x%x\n", header->e_machine);
                    break;
            }
        }
        return std::unique_ptr<IArchitecture>();
    }
}