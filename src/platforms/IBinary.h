//
// Created by Sascha Roth on 03.11.19.
//

#pragma once

namespace ChickenHook {

class IBinary {
    public:
        bool open(const std::string &path) = 0;
        bool close() = 0;
};

}