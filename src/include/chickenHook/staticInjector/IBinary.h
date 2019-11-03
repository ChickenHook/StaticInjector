//
// Created by Sascha Roth on 03.11.19.
//

#pragma once


#include <string>
#include <memory>
#include "architectures/IArchitecture.h"

namespace ChickenHook {

    class IBinary {
    public:

        static std::unique_ptr<IBinary> parseHeader(const std::string &path);

        virtual bool open() = 0;

        virtual bool close() = 0;

    protected:
        IBinary(const std::string &);

        virtual std::unique_ptr<IArchitecture> decideArchitecture() = 0;

    private:
    };

}