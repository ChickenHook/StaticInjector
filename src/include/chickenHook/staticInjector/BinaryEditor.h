//
// Created by Sascha Roth on 03.11.19.
//

#pragma once

#include "IBinary.h"
#include <string>
#include <memory>

namespace ChickenHook {

    class BinaryEditor {
    public:
        /**
         *
         * @param path to binary or shared library
         * @return
         */
        static std::unique_ptr<IBinary> open(const std::string &path);

        /**
         * Close file
         * @return
         */
        bool close();

        /**
         *
         * @param path to static library
         * @return
         */
        bool inject(const std::string &path);
    };

}