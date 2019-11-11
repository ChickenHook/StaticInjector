//
// Created by Sascha Roth on 11.11.19.
//

#include "Elf64Parser.h"
#include "IElfParser.h"
#include "tools/LoggingCallback.h"

namespace ChickenHook {


    bool Elf64Parser::iterateShdr(const std::function<bool(Elf64_Shdr *shdr)> &callback) {
        log("generateSymbolHooks [-] parsing headers...");
        auto *header = (Elf64_Ehdr *) &_data[0];

        log("generateSymbolHooks [-] search for symbols");
        for (int k = 0; k < header->e_shnum; k++) {
            auto shdr = &((Elf64_Shdr *) &_data[header->e_shoff])[k];

            if (!callback(shdr)) {
                return false;
            }
        }
        return true;
    }

    bool Elf64Parser::iterateSymbolTable(const std::vector<int> &types,
                                         const std::function<bool(int, char *, uint64_t,
                                                                  uint8_t)> function) {

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

        return iterateShdr([this, &function, &types, &strTab, &dynStrTab](Elf64_Shdr *shdr) {
            char *symbolName = nullptr;
            for (int type : types) {
                if (shdr->sh_type == type) { // shdr->sh_type == SHT_DYNSYM ||
                    char *tab = nullptr;
                    if (type == SHT_SYMTAB) {
                        tab = strTab;
                    } else if (type == SHT_DYNSYM) {
                        tab = dynStrTab;
                    }
                    if (tab == nullptr) {
                        return true;// can happen, this is no error!
                    }
                    for (size_t entry = 0;
                         (entry + 1) * sizeof(Elf64_Sym) <= shdr->sh_size; entry++) {
                        Elf64_Sym *sym = (Elf64_Sym *) (&_data[shdr->sh_offset] +
                                                        entry * sizeof(Elf64_Sym));
                        symbolName = tab + sym->st_name;
                        if (tab != nullptr &&
                            sym->st_name != 0 &&
                            sym->st_value != 0 &&
                            sym->st_info ==
                            0x12) { // only symbols that are implemented in our binary
                            //log("Found symbol: <%s> st_value<%lx> st_info<%lx> st_other<%lx>",
                            //    symbolName, sym->st_value, sym->st_info, sym->st_other);

                            if (!function(shdr->sh_type, symbolName, sym->st_value, sym->st_info)) {
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        });
    }

    bool Elf64Parser::iterateNeeded(const std::function<bool(char *)> function) {

        auto *dynamic = getSectionByName<Elf64_Shdr>(std::string(".dynamic"));
        if (dynamic == nullptr) {
            log("Could not find dynamic section!");
            return false;
        }
        auto *dynstr = getSectionByName<Elf64_Shdr>(".dynstr");
        if (dynstr == nullptr) {
            log("Could not find dynstr section!");
            return false;
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
                        if (!function(rpath)) {
                            return false;
                        }
                    }

                }
            }
        }
        return true;
    }

    Elf64Parser::Elf64Parser(std::vector<uint8_t> &data) : IElfParser(data) {}

    template<class K>
    K *Elf64Parser::getSectionByName(const std::string &name) {
        auto *header = (Elf64_Ehdr *) &_data[0];
        //shdrs[shstrtabIndex].sh_offset
        for (int k = 0; k < header->e_shnum; k++) {
            auto shdr = &((Elf64_Shdr *) &_data[header->e_shoff])[k];
            uint64_t off = (((Elf64_Shdr *) &_data[header->e_shoff]))[header->e_shstrndx].sh_offset;
            char *data = reinterpret_cast<char *>(&_data[off]);
            std::string sectionName(data + shdr->sh_name);
            //log("Found section <%s> off:<%lx> info<%lx> addr<%lx>", sectionName.c_str(),
            //   shdr->sh_offset, shdr->sh_info, shdr->sh_addr);
            //log("shdr %d %p %d %s", off, data, shdr->sh_name, sectionName.c_str());
            if (sectionName == name) {
                //Elf64_Dyn *dynamic = reinterpret_cast<Elf64_Dyn *>(&_data[shdr.sh_offset]);

                return (K *) shdr;
            }
        }
        return nullptr;
    }

}
