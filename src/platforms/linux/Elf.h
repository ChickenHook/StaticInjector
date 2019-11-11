//
// Created by Sascha Roth on 03.11.19.
//

#pragma once


#include <chickenHook/staticInjector/IBinary.h>
#include <fstream>
#include <vector>
#include <platforms/linux/parser/IElfParser.h>

namespace ChickenHook {


    class Elf : public IBinary {
    public:
    public:
        Elf(std::string string);

    public:

        /**
         * Determine if the given magic equals elf magic
         * @param magic the magic bytes
         * @return true if magic indicates an elf file
         */
        static bool isElf(std::vector<uint8_t> &);

        /**
         * Open the elf file
         * @return true on success
         */
        bool open() override;

        /**
         * close the elf file
         * @return true on success
         */
        bool close() override;

        /**
         * Replace the given dependency name with a random generated name
         * @param libraryToReplace the library to be replaced
         * @return the new dependency's libname
         */
        virtual const std::string replaceDependency(const std::string &libraryToReplace);

        /**
         * Print some information about the binary
         */
        virtual void printInfo();

        /**
         * NOT IMPLEMENTED YET
         * @param library
         */
        virtual void addLibraryDependency(const std::string &library);

        /**
         * Generates a cpp file that contains implementations of all exported symbols of the given library.
         *
         * This cpp file automatically loads the correct library at runtime and calls the corresponding symbol
         *
         * @param libraryName the name of the library to generate the implementations for
         * @param outputFileName the output filename of the headers
         */
        void generateSymbolHooks(const std::string &libraryName, const std::string &outputFileName);


    protected:
    /**
     * Returns the architecture.
     */
    uint32_t getArchitecture() override;

private:
    std::string _path;
    std::ifstream _is;
    std::vector<uint8_t> _data;
    std::unique_ptr<IElfParser> _elf_parser;


    /**
     * @return true if 64 bit
     */
        bool is64();


        /**
         * Tells us the endian format
         * @return true if endian format is little endian
         */
        bool isLittleEndian();

    };

}