//
// Created by Sascha Roth on 03.11.19.
//

#include "Elf.h"
#include "tools/HexDump.h"
#include <iostream>
#include <memory>
#include <utility>
#include <cstdio>
#include <cassert>
#include <fcntl.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <elf.h>
#include <tools/LoggingCallback.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <memory>
#include <sstream>
#include <limits>

#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <cassert>
#include <cstring>
#include <cerrno>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <link.h>
#include "generators/SymbolHookGenerator.h"
#include "platforms/linux/parser/Elf64Parser.h"

constexpr uint8_t ELF_MAGIC[]{
        0x7f,
        0x45,
        0x4c,
        0x46
};

namespace ChickenHook {

    /**
     * Determine if the given magic equals elf magic
     * @param magic the magic bytes
     * @return true if magic indicates an elf file
     */
    bool Elf::isElf(std::vector<uint8_t> &magic) {
        if (magic.empty()) {
            log("Magic array empty");
            return false;
        }
        if (magic.size() < sizeof(ELF_MAGIC)) {
            log("Magic array size to small");
            return false;
        }
        HexDump::hex_dump(&magic[0], magic.size(), std::cout);

        int i = 0;
        for (auto b:ELF_MAGIC) {
            if (b != magic[i]) {
                log("Magic doesn't match elf (%d) <%x> : <%x>", i, b, magic[i]);
                return false;
            }
            i++;
        }
        log("Found elf file");
        return true;
    }

    /**
     * Open the elf file
     * @return true on success
     */
    bool Elf::open() {
        _is.open(_path, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
        if (_is.good()) {
            std::ifstream::pos_type pos = _is.tellg();
            auto length = static_cast<unsigned int>(pos);
            _data.resize(length);
            _is.seekg(0, std::ios::beg);
            _is.read(reinterpret_cast<char *>(&_data[0]), length);
            printInfo();
            if (is64()) {
                _elf_parser = std::make_unique<Elf64Parser>(_data);
            } else {

            }
            return true;
        }
        return false;
    }

    /**
     * close the elf file
     * @return true on success
     */
    bool Elf::close() {
        if (_is.good())
            _is.close();
        return true;
    }

    Elf::Elf(std::string path) : IBinary(path), _is(), _path(std::move(path)) {
    }

    /**
     * @return true if 64 bit
     */
    bool Elf::is64() {
        bool is64 = false;
        switch (_data[EI_CLASS]) {
            case ELFCLASS64:
                is64 = true;
                break;
            case ELFCLASS32:
                break;
            default:
                log("UNKNOWN ARCHITECTURE");
                break; // TODO throw exception!
        }
        return is64;
    }

    /**
     * Tells us the endian format
     * @return true if endian format is little endian
     */
    bool Elf::isLittleEndian() {
        switch (_data[EI_DATA]) {
            case ELFDATA2LSB:
                return true;
            case ELFDATA2MSB:
                return false;
            default:
                log("INVALID endian format"); // TODO exception
                break;
        }
        return false;
    }

    /**
     *
     * Returns the architecture.
     *
     * You can use the following switch case to determine the architecture
     * switch (header->e_machine) {
     *     case EM_NONE:
     *         log("None (0x0)");
     *         break;
     *
     *     case EM_386:
     *         log("INTEL x86 (0x%x)", EM_386);
     *         break;
     *
     *     case EM_X86_64:
     *         log("AMD x86_64 (0x%x)", EM_X86_64);
     *         break;
     *
     *     case EM_AARCH64:
     *         log("AARCH64 (0x%x)", EM_AARCH64);
     *         break;
     *
     *     case EM_ARM:
     *         log("ARM (0x%x)", EM_ARM);
     *         break;
     *     default:
     *         log(" 0x%x", header->e_machine);
     *         break;
    }*/
    uint32_t Elf::getArchitecture() {
        if (is64()) {
            auto *header = (Elf64_Ehdr *) &_data[0];
            return header->e_machine;
        } else {
            auto *header = (Elf32_Ehdr *) &_data[0];
            return header->e_machine;
        }
    }






    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////// REPLACE DEPENDENCY //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /**
     * Generates a cpp file that contains implementations of all exported symbols of the given library.
     *
     * This cpp file automatically loads the correct library at runtime and calls the corresponding symbol
     *
     * @param libraryName the name of the library to generate the implementations for
     * @param outputFileName the output filename of the headers
     */
    void
    Elf::generateSymbolHooks(const std::string &libraryName, const std::string &outputFileName) {
        SymbolHookGenerator symbolHookGenerator;
        if (!symbolHookGenerator.open(outputFileName)) {
            log("generateSymbolHooks [-] could not open <%s>", outputFileName);
            return;
        }

        std::vector<int> types;
        types.push_back(SHT_SYMTAB);
        types.push_back(SHT_DYNSYM);

        if (!_elf_parser->iterateSymbolTable(types,
                                             [this, &symbolHookGenerator](int type,
                                                                          char *symbolName,
                                                                          uint64_t st_value,
                                                                          uint8_t st_info) {

                                                 log("Adding: <%s> type<%lx> st_value<%lx> st_info<%lx> st_other<%lx>",
                                                     symbolName, type, st_value, st_info);
                                                 symbolHookGenerator.addSymbol(symbolName);
                                                 return true;
                                             })) {
            log("Error while iterate symbols, abort...");
            return;
        }
        symbolHookGenerator.addDlOpen(libraryName);
        log("Symbol hooks generation finished");
        symbolHookGenerator.close();
    }

    /**
     * Replace the given dependency name with a random generated name
     * @param libraryToReplace the library to be replaced
     * @return the new dependency's libname
     */
    const std::string Elf::replaceDependency(const std::string &libraryToReplace) {
        std::string newLibName("lib");

        if (!_elf_parser->iterateNeeded([this, &libraryToReplace, &newLibName](char *needed) {

            std::string lib(needed);
            if (lib == libraryToReplace) {
                int chars = strlen(needed) - 6;// reduce by .so and lib
                if (chars <= 0) {
                    log("Invalid library name length, skip");
                    return true; // can happen
                }
                for (int k = 0; k < chars; k++) {
                    newLibName += "a";
                }
                newLibName += ".so";
                log("Replace <%s> with <%s>", needed, newLibName.c_str());
                strcpy(needed, newLibName.c_str());
            }
            return true;
        })) {
            log("Error while iterate needed, abort...");
            return;
        }

        // write changes
        _is.close();
        //_is.open(_path, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
        std::ofstream _os(_path);
        _os.write(reinterpret_cast<const char *>(&_data[0]), _data.size());
        _os.close();
        open();
        return newLibName;
    }

    /**
     * Print some information about the binary
     */
    void Elf::printInfo() {
        log("Library info:");
        log("   Name: <%s>", _path.c_str());
        switch (getArchitecture()) {
            case EM_NONE:
                log("   Arch: None (0x0)");
                break;

            case EM_386:
                log("   Arch: INTEL x86 (0x%x)", EM_386);
                break;

            case EM_X86_64:
                log("   Arch: AMD x86_64 (0x%x)", EM_X86_64);
                break;

            case EM_AARCH64:
                log("   Arch: AARCH64 (0x%x)", EM_AARCH64);
                break;

            case EM_ARM:
                log("   Arch: ARM (0x%x)", EM_ARM);
                break;
            default:
                log("   Arch:  0x%x", getArchitecture());
                break;

        }
        if (isLittleEndian()) {
            log("   Endian format: LSB");
        } else if (isLittleEndian()) {
            log("   Endian format: MSB");
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INJECT DEPENDENCY *** EXPERIMENTAL *** ** WIP ** ////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Elf::addLibraryDependency(const std::string &library) {
        log("NOT IMPLEMENTED");
    }
}