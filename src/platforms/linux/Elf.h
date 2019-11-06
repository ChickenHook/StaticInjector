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

        virtual void replaceDependency(const std::string &);

        virtual void printInfo();



    protected:
        uint32_t getArchitecture() override;

    private:
        std::string _path;
        std::ifstream _is;
        std::vector<uint8_t> _data;

        template<class K>
        K *getSectionByName(const std::string &name);

        bool is64();

        bool isLittleEndian();
    };

}