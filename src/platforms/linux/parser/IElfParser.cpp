//
// Created by Sascha Roth on 11.11.19.
//

#include "IElfParser.h"
#include <utility>

ChickenHook::IElfParser::IElfParser(std::vector<uint8_t> &data) : _data(data) {
}

