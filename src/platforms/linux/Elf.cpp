//
// Created by Sascha Roth on 03.11.19.
//

#include "Elf.h"
#include "tools/HexDump.h"
#include <iostream>
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
    switch (header->e_machine) {
        case EM_NONE:
            log("None (0x0)");
            break;

        case EM_386:
            log("INTEL x86 (0x%x)", EM_386);
            break;

        case EM_X86_64:
            log("AMD x86_64 (0x%x)", EM_X86_64);
            break;

        case EM_AARCH64:
            log("AARCH64 (0x%x)", EM_AARCH64);
            break;

        case EM_ARM:
            log("ARM (0x%x)", EM_ARM);
            break;
        default:
            log(" 0x%x", header->e_machine);
            break;

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


    /**
     * Returns the corresponding section by the given name
     * @tparam  K the type of the section (Elf64_Ehdr, or Elf32_Ehdr)
     * @param   name The name of the section
     * @return  null on failure
     *          the section on success
     */
    template<class K>
    K *Elf::getSectionByName(const std::string &name) {
        if (is64()) {
            auto *header = (Elf64_Ehdr *) &_data[0];
            //shdrs[shstrtabIndex].sh_offset
            for (int k = 0; k < header->e_shnum; k++) {
                auto shdr = &((Elf64_Shdr *) &_data[header->e_shoff])[k];
                uint64_t off = (((Elf64_Shdr *) &_data[header->e_shoff]))[header->e_shstrndx].sh_offset;
                char *data = reinterpret_cast<char *>(&_data[off]);
                std::string sectionName(data + shdr->sh_name);
                //log("shdr %d %p %d %s", off, data, shdr->sh_name, sectionName.c_str());
                if (sectionName == name) {
                    //Elf64_Dyn *dynamic = reinterpret_cast<Elf64_Dyn *>(&_data[shdr.sh_offset]);

                    return (K *) shdr;
                }
            }
        } else {
            auto *header = (Elf32_Ehdr *) &_data[0];
            //shdrs[shstrtabIndex].sh_offset
            for (int k = 0; k < header->e_shnum; k++) {
                auto shdr = &((Elf32_Shdr *) &_data[header->e_shoff])[k];
                int off = (((Elf32_Shdr *) &_data[header->e_shoff]))[header->e_shstrndx].sh_offset;
                char *data = reinterpret_cast<char *>(&_data[off]);
                std::string sectionName(data + shdr->sh_name);
                //log("shdr %d %p %d %s", off, data, shdr->sh_name, sectionName.c_str());
                if (sectionName == name) {
                    //Elf64_Dyn *dynamic = reinterpret_cast<Elf64_Dyn *>(&_data[shdr.sh_offset]);

                    return (K *) shdr;
                }
            }
        }

        return nullptr;
    }

    void Elf::replaceDependency(const std::string &symbol) {
        if (is64()) {
            auto *dynamic = getSectionByName<Elf64_Shdr>(std::string(".dynamic"));
            if (dynamic == nullptr) {
                log("Could not find dynamic section!");
                return;
            }
            auto *dynstr = getSectionByName<Elf64_Shdr>(".dynstr");
            if (dynstr == nullptr) {
                log("Could not find dynstr section!");
                return;
            }
            char *strTab = reinterpret_cast<char *>(&_data[dynstr->sh_offset]);

            /// strtab2
            char *rpath = nullptr;
            log("Searching for libraries in dynamic section");

            auto *dyn = (Elf64_Dyn *) (&_data[(dynamic->sh_offset)]);
            for (; dyn->d_tag != DT_NULL; dyn++) {
                if (dyn->d_tag == DT_NEEDED) {
                    if (dyn->d_un.d_val != 0) {
                        rpath = strTab + dyn->d_un.d_val;
                        if (rpath != nullptr) {
                            log("Found Library <%s>", rpath);

                            // TEST
                            std::string lib(rpath);
                            if (lib == symbol) {
                                int chars = strlen(rpath) - 6;// reduce by .so and lib
                                if (chars <= 0) {
                                    log("Invalid library name length, skip");
                                    continue;
                                }
                                std::string newLibName("lib");
                                for (int k = 0; k < chars; k++) {
                                    newLibName += "a";
                                }
                                newLibName += ".so";
                                log("Replace <%s> with <%s>", rpath, newLibName.c_str());
                                strcpy(rpath, newLibName.c_str());
                            }
                        }
                    }
                }
            }
        } else {
            auto *dynamic = getSectionByName<Elf32_Shdr>(std::string(".dynamic"));
            if (dynamic == nullptr) {
                log("Could not find dynamic section!");
                return;
            }
            auto *dynstr = getSectionByName<Elf32_Shdr>(".dynstr");
            if (dynstr == nullptr) {
                log("Could not find dynstr section!");
                return;
            }
            char *strTab = reinterpret_cast<char *>(&_data[dynstr->sh_offset]);

            /// strtab2
            char *rpath = nullptr;
            log("Searching for libraries in dynamic section");

            auto *dyn = (Elf32_Dyn *) (&_data[(dynamic->sh_offset)]);
            for (; dyn->d_tag != DT_NULL; dyn++) {
                if (dyn->d_tag == DT_NEEDED) {
                    if (dyn->d_un.d_val != 0) {
                        rpath = strTab + dyn->d_un.d_val;
                        if (rpath != nullptr) {
                            log("Found Library <%s>", rpath);

                            // TEST
                            std::string lib(rpath);
                            if (lib == symbol) {
                                int chars = strlen(rpath) - 6;// reduce by .so and lib
                                if (chars <= 0) {
                                    log("Invalid library name length, skip");
                                    continue;
                                }
                                std::string newLibName("lib");
                                for (int k = 0; k < chars; k++) {
                                    newLibName += "a";
                                }
                                newLibName += ".so";
                                log("Replace <%s> with <%s>", rpath, newLibName.c_str());
                                strcpy(rpath, newLibName.c_str());
                            }
                        }
                    }
                }
            }
        }

        // write changes
        _is.close();
        //_is.open(_path, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
        std::ofstream _os(_path);
        _os.write(reinterpret_cast<const char *>(&_data[0]), _data.size());
        _os.close();
        open();
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

}