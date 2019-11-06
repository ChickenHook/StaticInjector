//
// Created by Sascha Roth on 03.11.19.
//

#pragma once


#include <string>
#include <memory>


namespace ChickenHook {

    class IBinary {
    public:

        static std::unique_ptr<IBinary> parseHeader(const std::string &path);

        virtual bool open() = 0;

        virtual bool close() = 0;

        virtual void replaceDependency(const std::string &) = 0;

        virtual void printInfo() = 0;

    protected:
        IBinary(const std::string &);

        virtual uint32_t getArchitecture() = 0;

    private:
    };

}