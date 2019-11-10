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

        virtual void addLibraryDependency(const std::string &library);

        void generateSymbolHooks(const std::string &libraryName, const std::string &outputFileName);


    protected:
        uint32_t getArchitecture() override;

    private:
        std::string _path;
        std::ifstream _is;
        std::vector<uint8_t> _data;

        template<class K>
        K *getSectionByName(const std::string &name);

        template<class K>
        K *getSectionById(const int id);

        bool is64();

        bool isLittleEndian();


        void resize(uint32_t newLen);

        int moveSectionToEndAndResize(const std::string &section, uint32_t newAdditionalSectionLen,
                                      bool end, bool searchPhdr);

        void
        addVersionDependency(const std::string &name, const int strId, const int newDystrOffset);


        template<class K>
    std::string getSectionName(K *section);

        void patchVerneed(int additionalEntriesCount, int newOffset, int newVerSymOffset);

    };

}