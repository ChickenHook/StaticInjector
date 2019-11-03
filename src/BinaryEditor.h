//
// Created by Sascha Roth on 03.11.19.
//

#pragma once

namespace ChickenHook {

class BinaryEditor {
public:
    bool open(const std::string &path);

    bool close();

    bool inject(const IBinary &binary);

};

}