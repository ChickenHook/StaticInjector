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
#include <generators/SymbolHookGenerator.h>

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

    template<class K>
    std::string Elf::getSectionName(K *Tsection) {
        if (is64()) {
            Elf64_Shdr *section = (Elf64_Shdr *) Tsection;
            auto *header = (Elf64_Ehdr *) &_data[0];
            uint64_t off = (((Elf64_Shdr *) &_data[header->e_shoff]))[header->e_shstrndx].sh_offset;
            char *data = reinterpret_cast<char *>(&_data[off]);
            std::string sectionName(data + section->sh_name);
            return sectionName;
        }
        return "";
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
                //log("Found section <%s> off:<%lx> info<%lx> addr<%lx>", sectionName.c_str(),
                //    shdr->sh_offset, shdr->sh_info, shdr->sh_addr);
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

                //log("Found section <%s> off:<%lx> info<%lx> addr<%lx>", sectionName.c_str(),
                //    shdr->sh_offset, shdr->sh_info, shdr->sh_addr);
                //log("shdr %d %p %d %s", off, data, shdr->sh_name, sectionName.c_str());
                if (sectionName == name) {
                    //Elf64_Dyn *dynamic = reinterpret_cast<Elf64_Dyn *>(&_data[shdr.sh_offset]);

                    return (K *) shdr;
                }
            }
        }

        return nullptr;
    }

    /**
 * Returns the corresponding section by the given name
 * @tparam  K the type of the section (Elf64_Ehdr, or Elf32_Ehdr)
 * @param   name The name of the section
 * @return  null on failure
 *          the section on success
 */
    template<class K>
    K *Elf::getSectionById(const int id) {
        if (is64()) {
            auto *header = (Elf64_Ehdr *) &_data[0];

            if (id > header->e_shnum) {
                log("Error while retrieve section by id, invalid id");
                return nullptr;
            }
            return &((K *) &_data[header->e_shoff])[id];

        } else {
            auto *header = (Elf32_Ehdr *) &_data[0];

            if (id > header->e_shnum) {
                log("Error while retrieve section by id, invalid id");
                return nullptr;
            }
            return &((K *) &_data[header->e_shoff])[id];
        }

        return nullptr;
    }





    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////// REPLACE DEPENDENCY //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    void
    Elf::generateSymbolHooks(const std::string &libraryName, const std::string &outputFileName) {
        SymbolHookGenerator symbolHookGenerator;
        if (!symbolHookGenerator.open(outputFileName)) {
            log("generateSymbolHooks [-] could not open <%s>", outputFileName);
            return;
        }

        if (_data.size() == 0) {
            log("generateSymbolHooks [-] Library is not loaded, abort...");
            return;
        }
        if (is64()) {
            log("generateSymbolHooks [-] write source into <%s>", outputFileName.c_str());
            log("generateSymbolHooks [-] parsing headers...");
            auto *header = (Elf64_Ehdr *) &_data[0];

            char *dynStrTab = nullptr;
            auto *dynstr = getSectionByName<Elf64_Shdr>(".dynstr");
            if (dynstr == nullptr) {
                log("!! warning !! Could not find dynstr section!");
            } else {
                dynStrTab = reinterpret_cast<char *>(&_data[dynstr->sh_offset]);
            }
            char *strTab = nullptr;
            auto *strtab = getSectionByName<Elf64_Shdr>(".strtab");
            if (strtab == nullptr) {
                log("!! warning !! Could not find strtab section!");
            } else {
                strTab = reinterpret_cast<char *>(&_data[strtab->sh_offset]);
            }


            char *symbolName = nullptr;

            log("generateSymbolHooks [-] search for symbols");
            for (int k = 0; k < header->e_shnum; k++) {
                auto shdr = &((Elf64_Shdr *) &_data[header->e_shoff])[k];
                if (shdr->sh_type == SHT_SYMTAB) { // shdr->sh_type == SHT_DYNSYM ||
                    for (size_t entry = 0;
                         (entry + 1) * sizeof(Elf64_Sym) <= shdr->sh_size; entry++) {
                        Elf64_Sym *sym = (Elf64_Sym *) (&_data[shdr->sh_offset] +
                                                        entry * sizeof(Elf64_Sym));
                        symbolName = strTab + sym->st_name;
                        if (strTab != nullptr &&
                            sym->st_name != 0 &&
                            sym->st_value != 0 &&
                            sym->st_info ==
                            0x12) { // only symbols that are implemented in our binary
                            log("Found symbol: <%s> st_value<%lx> st_info<%lx> st_other<%lx>",
                                symbolName, sym->st_value, sym->st_info, sym->st_other);
                            symbolHookGenerator.addSymbol(symbolName);
                        }
                    }
                } else if (shdr->sh_type == SHT_DYNSYM) { // shdr->sh_type == SHT_DYNSYM ||
                    for (size_t entry = 0;
                         (entry + 1) * sizeof(Elf64_Sym) <= shdr->sh_size; entry++) {
                        Elf64_Sym *sym = (Elf64_Sym *) (&_data[shdr->sh_offset] +
                                                        entry * sizeof(Elf64_Sym));
                        symbolName = dynStrTab + sym->st_name;
                        if (dynstr != nullptr &&
                            sym->st_name != 0 &&
                            sym->st_value != 0 &&
                            sym->st_info ==
                            0x12) { // only symbols that are implemented in our binary
                            log("Found symbol: <%s> st_value<%lx> st_info<%lx> st_other<%lx>",
                                symbolName, sym->st_value, sym->st_info, sym->st_other);
                            symbolHookGenerator.addSymbol(symbolName);
                        }
                    }
                }
            }
        }
        symbolHookGenerator.addDlOpen(libraryName);
        symbolHookGenerator.close();
    }

    void Elf::replaceDependency(const std::string &libraryToReplace) {
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
                            if (lib == libraryToReplace) {
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
                            if (lib == libraryToReplace) {
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////// INJECT DEPENDENCY *** EXPERIMENTAL *** ** WIP ** ////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Elf::resize(uint32_t newLen) {
        this->_data.resize(newLen);
    }

    int
    Elf::moveSectionToEndAndResize(const std::string &section, uint32_t newAdditionalSectionLen,
                                   bool end, bool searchPhdr) {
        log("moveSectionToEndAndResize [-] move section <%s>", section.c_str());
        if (is64()) {
            Elf64_Shdr *sectionHeader = getSectionByName<Elf64_Shdr>(section);

            Elf64_Off oldOffset = sectionHeader->sh_offset;
            Elf64_Xword oldSize = sectionHeader->sh_size;
            uint32_t newLen = oldSize + newAdditionalSectionLen;
            Elf64_Off newOffset = _data.size();

            log("moveSectionToEndAndResize [-] lib addr <%p>", &_data[0]);
            log("moveSectionToEndAndResize [-] section addr <%p>", sectionHeader);
            log("moveSectionToEndAndResize [-] section offset addr <%p>",
                &sectionHeader->sh_offset);
            log("moveSectionToEndAndResize [-] old section offset <%lx>", oldOffset);
            log("moveSectionToEndAndResize [-] new section offset <%lx>", newOffset);
            log("moveSectionToEndAndResize [-] old section size <%lx>", oldSize);
            log("moveSectionToEndAndResize [-] new section size <%lx>", newLen);

            int newLibSize = _data.size() + newLen;
            log("moveSectionToEndAndResize [-] old lib size <%d>", _data.size());
            log("moveSectionToEndAndResize [-] new lib size <%d>", newLibSize);
            _data.resize(newLibSize);

            // copy this sh
            Elf64_Shdr newHeader;
            memcpy(&newHeader, sectionHeader, sizeof(Elf64_Shdr));
            // set new offset
            newHeader.sh_offset = newOffset;
            newHeader.sh_addr = newOffset;


            // set new len
            newHeader.sh_size = newLen;
            memcpy(sectionHeader, &newHeader, sizeof(Elf64_Shdr));
            Elf64_Shdr *sectionHeader2 = getSectionByName<Elf64_Shdr>(section);
            log("moveSectionToEndAndResize [-] updated section offset <%p> <%lx> <%lx> <%lx>",
                &sectionHeader2->sh_offset, sectionHeader2->sh_offset, sectionHeader->sh_offset,
                newHeader.sh_offset);


            // copy the section
            if (end) {
                memcpy(&_data[newOffset + newAdditionalSectionLen], &_data[oldOffset], oldSize);

            } else {
                memcpy(&_data[newOffset], &_data[oldOffset], oldSize);
            }

            if (searchPhdr) {
                log("moveSectionToEndAndResize [-] let's search for the corresponding phdr");
                auto *header = (Elf64_Ehdr *) &_data[0];
                bool found = false;
                for (int k = 0; k < header->e_phnum; k++) {
                    auto phdr = &((Elf64_Phdr *) &_data[header->e_phoff])[k];
                    log("moveSectionToEndAndResize [-] found phdr p_offset<%lx> p_type<%lx> p_vaddr<%lx>",
                        phdr->p_offset, phdr->p_type, phdr->p_vaddr);
                    if (phdr->p_offset == oldOffset) {
                        log("Found phdr for dynamic section!");
                        phdr->p_paddr = newOffset + (phdr->p_paddr - phdr->p_offset);
                        phdr->p_vaddr = newOffset + (phdr->p_vaddr - phdr->p_offset);
                        phdr->p_offset = newOffset;
                        log("moveSectionToEndAndResize [-] successful moved to phdr p_offset<%lx> p_type<%lx> p_vaddr<%lx>",
                            phdr->p_offset, phdr->p_type, phdr->p_vaddr);

                        found = true;
                        break;
                    }
                }
                if (!found) {
                    log("!!WARNING!! Could not find corresponding dynamic phdr...");
                }
            }

            log("moveSectionToEndAndResize [-] done");

            return newOffset;
        } else {

        }

        return 0;
    }

    void Elf::addLibraryDependency(const std::string &library) {

        log("add library dependency <%s>", library.c_str());
        if (is64()) {
            // retrieve dynamic and dynstr sections
            Elf64_Shdr *dynstrSectionAddr = getSectionByName<Elf64_Shdr>(".dynstr");

            // calculate size of bytes to inject
            int additionalDynamicLen = sizeof(Elf64_Dyn);
            int additionalDynstrLen = library.size() + 1;// string size + \0


            int off = moveSectionToEndAndResize(".dynamic",
                                                additionalDynamicLen, true, false);
            off = moveSectionToEndAndResize(".dynamic",
                                            additionalDynamicLen, true, true);
            // edit dynamic

            Elf64_Dyn *testDyn = reinterpret_cast<Elf64_Dyn *>(&_data[off]);
            memcpy(testDyn, dynstrSectionAddr, sizeof(Elf64_Dyn));
            testDyn->d_un.d_ptr = dynstrSectionAddr->sh_size;//dynstrSectionAddr->sh_size
            testDyn->d_un.d_val = dynstrSectionAddr->sh_size;//dynstrSectionAddr->sh_size
            testDyn->d_tag = DT_NEEDED;


//            wri(newDyn.d_un.d_val, j);


            int newOffset = moveSectionToEndAndResize(".dynstr",
                                                      additionalDynstrLen, false, false);
            const char *newLibName = library.c_str();
            memcpy(&_data[newOffset + dynstrSectionAddr->sh_size], newLibName,
                   strlen(newLibName) + 1);

            addVersionDependency(library, testDyn->d_un.d_val, newOffset);

            // write changes
            _is.close(); // TODO put into function
            //_is.open(_path, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
            std::ofstream _os(_path);
            _os.write(reinterpret_cast<const char *>(&_data[0]), _data.size());
            _os.close();
            open();

        } else {

        }
    }

    void Elf::patchVerneed(int additionalEntriesCount, int newOffset, int newVerSymOffset) {
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
                if (dyn->d_tag == DT_VERNEEDNUM) {
                    if (dyn->d_un.d_val != 0) {
                        log("Found VERNEEDNUM <%lx> <%p>", dyn->d_un.d_val, dyn->d_un.d_ptr);
                        dyn->d_un.d_val = dyn->d_un.d_val + additionalEntriesCount;
                        dyn->d_un.d_ptr = dyn->d_un.d_ptr + additionalEntriesCount;
                    }
                } else if (dyn->d_tag == DT_VERNEED) {
                    if (dyn->d_un.d_val != 0) {
                        log("Found VERNEED <%lx> <%p>", dyn->d_un.d_val, dyn->d_un.d_ptr);
                        dyn->d_un.d_val = newOffset;
                        dyn->d_un.d_ptr = newOffset;
                    }
                } else if (dyn->d_tag == DT_VERSYM) {
                    log("Found DT_VERSYM <%lx> <%p>", dyn->d_un.d_val, dyn->d_un.d_ptr);
                    //dyn->d_un.d_val = newVerSymOffset;
                    //dyn->d_un.d_ptr = newVerSymOffset;

                } else if (dyn->d_tag == DT_VERDEF) {
                    log("Found DT_VERDEF <%lx> <%p>", dyn->d_un.d_val, dyn->d_un.d_ptr);
                    //dyn->d_un.d_val = newVerSymOffset;
                    //dyn->d_un.d_ptr = newVerSymOffset;

                } /*else if(dyn->d_tag == DT_NEEDED) {
                    log("Found DT_NEEDED <%lx> <%p>", dyn->d_un.d_val, dyn->d_un.d_ptr);
                }*/
            }
        }
    }

    void
    Elf::addVersionDependency(const std::string &name, const int strId, const int newDystrOffset) {
        if (is64()) {
            Elf64_Shdr *gnuVersionSection = getSectionByName<Elf64_Shdr>(".gnu.version_r"); //_r

            Elf64_Shdr *gnuVersionStringsSection = getSectionById<Elf64_Shdr>(
                    gnuVersionSection->sh_link);


            char *strTab = reinterpret_cast<char *>(&_data[gnuVersionStringsSection->sh_offset]);

            std::string versionStringsSectionName = getSectionName<Elf64_Shdr>(
                    gnuVersionStringsSection);
            log("versionStringsSectionName: <%s>", versionStringsSectionName.c_str());
            if (versionStringsSectionName.compare(".dynstr") != 0) {
                log("version dependency strings not in .dynstr... not supported yet");
                return; // TODO crash?
            }
            //gnuVersionSection->sh_link = newDystrOffset;

            char *rpath = nullptr;
            int rel_offset = 0;
            Elf64_Verneed *verneed = (Elf64_Verneed *) &_data[gnuVersionSection->sh_offset];
            while (verneed != nullptr) {
                rpath = strTab + verneed->vn_file;
                log("Found verneed vn_file<%lx> vn_version<%lx> vn_next<%lx> vn_file<%lx> name<%s> vn_aux<%lx> rel_offset<%lx>",
                    verneed->vn_file, verneed->vn_version, verneed->vn_next, verneed->vn_file,
                    rpath, verneed->vn_aux,
                    rel_offset);
                if (verneed->vn_next == 0) {
                    log("No more verneeds found");
                    break;
                }
                rel_offset += verneed->vn_next;
                verneed = reinterpret_cast<Elf64_Verneed *>((char *) verneed + verneed->vn_next);
            }

            // modify
            Elf64_Verneed newVerneed;
            newVerneed.vn_file = strId;
            newVerneed.vn_next = 0;
            newVerneed.vn_cnt = 1;
            newVerneed.vn_aux = 0x10;
            newVerneed.vn_version = 1;

            int oldVersionSectionSize = gnuVersionSection->sh_size;


            int oldSize = gnuVersionSection->sh_size;
            int oldOff = gnuVersionSection->sh_offset;
            int newSize = sizeof(Elf64_Verneed) + sizeof(Elf64_Vernaux);
            int newOffset = moveSectionToEndAndResize(".gnu.version_r",
                                                      newSize, false, false);

            Elf64_Verneed *testVerneed = reinterpret_cast<Elf64_Verneed *>(&_data[newOffset]);

            log("new verneed address <%p> ", testVerneed);
            log("Add new verneed <%p> vn_file<%lx> vn_version<%lx> vn_next<%lx> name<%s> vn_aux<%lx>",
                ((char *) testVerneed) + oldVersionSectionSize,
                newVerneed.vn_file, newVerneed.vn_version, newVerneed.vn_next, name.c_str(),
                newVerneed.vn_aux);

            memcpy(((char *) testVerneed) + oldVersionSectionSize, &newVerneed,
                   sizeof(Elf64_Verneed));
            //gnuVersionSection->sh_size = gnuVersionSection->sh_size + sizeof(Elf64_Verneed); // update sh size
            Elf64_Vernaux newVernaux;
            newVernaux.vna_name = strId;
            newVernaux.vna_flags = 0;
            newVernaux.vna_hash = 0;
            newVernaux.vna_other = 2;
            newVernaux.vna_next = 0;
            memcpy(((char *) testVerneed) + oldVersionSectionSize + sizeof(Elf64_Verneed),
                   &newVernaux,
                   sizeof(Elf64_Vernaux));

            // test
            Elf64_Shdr *newGnuVersionSection = getSectionByName<Elf64_Shdr>(".gnu.version_r"); //_r
            newGnuVersionSection->sh_info = newGnuVersionSection->sh_info + 1;
            verneed = (Elf64_Verneed *) &_data[newGnuVersionSection->sh_offset];
            log("new verneed address <%p> ", verneed);
            rel_offset = 0;
            while (verneed != nullptr) {
                rpath = strTab + verneed->vn_file;
                log("AFTER MODIFY: Found verneed <%p> vn_file<%lx> vn_version<%lx> vn_next<%lx> vn_file<%lx> name<%s> vn_aux<%lx> rel_offset<%lx>",
                    verneed,
                    verneed->vn_file, verneed->vn_version, verneed->vn_next, verneed->vn_file,
                    rpath, verneed->vn_aux,
                    rel_offset);
                Elf64_Vernaux *vernaux = (Elf64_Vernaux *) (((char *) verneed + verneed->vn_aux));
                while (vernaux != nullptr) {
                    log("AFTER MODIFY: Found vernaux <%p> vna_hash<%lx> vna_flags<%lx> vna_other<%lx> vna_name<%lx>",
                        vernaux,
                        vernaux->vna_hash, vernaux->vna_flags, vernaux->vna_other,
                        vernaux->vna_name);
                    if (vernaux->vna_next == 0) {
                        break;
                    }
                    vernaux = reinterpret_cast<Elf64_Vernaux *>(((char *) vernaux +
                                                                 vernaux->vna_next));
                }

                if (verneed->vn_next == 0) {
                    log("No more verneeds found");
                    break;
                }
                rel_offset += verneed->vn_next;
                verneed = reinterpret_cast<Elf64_Verneed *>((char *) verneed + verneed->vn_next);
            }
            verneed->vn_next =
                    (oldSize - rel_offset); // calculate offset to our new verneed
            patchVerneed(1, newOffset, newDystrOffset);

        }


    }


//    template<ElfFileParams>
//    std::string & ElfFile<ElfFileParamNames>::replaceSection(const SectionName & sectionName,
//                                                             unsigned int size)
//    {
//        ReplacedSections::iterator i = replacedSections.find(sectionName);
//        std::string s;
//
//        if (i != replacedSections.end()) {
//            s = std::string(i->second);
//        } else {
//            Elf_Shdr & shdr = findSection(sectionName);
//            s = std::string((char *) contents + rdi(shdr.sh_offset), rdi(shdr.sh_size));
//        }
//
//        s.resize(size);
//        replacedSections[sectionName] = s;
//
//        return replacedSections[sectionName];
//    }


//    template<ElfFileParams>
//    void ElfFile<ElfFileParamNames>::addNeeded(const std::set<std::string> & libs)
//    {
//        if (libs.empty()) return;
//
//        Elf_Shdr & shdrDynamic = findSection(".dynamic");
//        Elf_Shdr & shdrDynStr = findSection(".dynstr");
//
//        /* add all new libs to the dynstr string table */
//        unsigned int length = 0;
//        for (auto & i : libs) length += i.size() + 1;
//
//        std::string & newDynStr = replaceSection(".dynstr",
//                                                 rdi(shdrDynStr.sh_size) + length + 1);
//        std::set<Elf64_Xword> libStrings;
//        unsigned int pos = 0;
//        for (auto & i : libs) {
//            setSubstr(newDynStr, rdi(shdrDynStr.sh_size) + pos, i + '\0');
//            libStrings.insert(rdi(shdrDynStr.sh_size) + pos);
//            pos += i.size() + 1;
//        }
//
//        /* add all new needed entries to the dynamic section */
//        std::string & newDynamic = replaceSection(".dynamic",
//                                                  rdi(shdrDynamic.sh_size) + sizeof(Elf_Dyn) * libs.size());
//
//        unsigned int idx = 0;
//        for ( ; rdi(((Elf_Dyn *) newDynamic.c_str())[idx].d_tag) != DT_NULL; idx++) ;
//        debug("DT_NULL index is %d\n", idx);
//
//        /* Shift all entries down by the number of new entries. */
//        setSubstr(newDynamic, sizeof(Elf_Dyn) * libs.size(),
//                  std::string(newDynamic, 0, sizeof(Elf_Dyn) * (idx + 1)));
//
//        /* Add the DT_NEEDED entries at the top. */
//        unsigned int i = 0;
//        for (auto & j : libStrings) {
//            Elf_Dyn newDyn;
//            wri(newDyn.d_tag, DT_NEEDED);
//            wri(newDyn.d_un.d_val, j);
//            setSubstr(newDynamic, i * sizeof(Elf_Dyn), std::string((char *) &newDyn, sizeof(Elf_Dyn)));
//            i++;
//        }
//
//        changed = true;
//    }
}