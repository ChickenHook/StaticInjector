//
// Created by sascharoth on 11.11.19.
//

#pragma once


#include <elf.h>
#include "IElfParser.h"

namespace ChickenHook {

    class Elf32Parser : public IElfParser {


    public:
        Elf32Parser(std::vector<uint8_t> &data);


        bool iterateNeeded(const std::function<bool(char *)> function) override;

        bool iterateShdr(const std::function<bool(Elf32_Shdr *shdr)>& callback);


        template<class K>
        K *getSectionByName(const std::string &name);

        bool iterateSymbolTable(const std::vector<int> &types,
                                const std::function<bool(int, char *, uint64_t, uint8_t)> function) override;
    };

}