//
// Created by Sascha Roth on 10.11.19.
//


#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>

namespace ChickenHook {

    class SymbolHookGenerator {
    public:
        SymbolHookGenerator();

        bool open(const std::string &file);

        void addDlOpen(const std::string &library);

        void addSymbol(const std::string &symbol);

        void close();

    private:
        std::ofstream _os;
        std::set<std::string> _symbols;
        std::string _library_name;

        void addString(const std::string &file);


        void apply();
    };
}