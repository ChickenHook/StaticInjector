//
// Created by Sascha Roth on 03.11.19.
//

#pragma once


#include <chickenHook/staticInjector/IBinary.h>
#include <fstream>
#include <vector>

namespace ChickenHook {


    class Elf : public IBinary {
    public:
    public:
        Elf(std::string string);

    public:
        static bool isElf(std::vector<uint8_t> &);

        bool open() override;

        bool close() override;

    protected:
        std::unique_ptr<IArchitecture> decideArchitecture() override;

    private:
        std::string _path;
        std::ifstream _is;
        std::vector<uint8_t> _data;
    };

}