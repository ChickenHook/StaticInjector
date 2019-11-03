//
// Created by Sascha Roth on 03.11.19.
//

#pragma once

#include <string>

namespace ChickenHook {

    class BinaryEditor {
    public:
        /**
         *
         * @param path to binary or shared library
         * @return
         */
        bool open(const std::string &path);

        bool close();

        /**
         *
         * @param path to static library
         * @return
         */
        bool inject(const std::string &path);
    };

}