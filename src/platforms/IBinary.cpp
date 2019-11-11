//
// Created by Sascha Roth on 03.11.19.
//

#include "chickenHook/staticInjector/IBinary.h"
#include <fstream>
#include <vector>
#include <platforms/linux/Elf.h>

constexpr int MAGIC_BUFF_SIZE(64);
namespace ChickenHook {

    /**
     * Parses the first few of the given binary and instantiates a object representation
     *
     * We have to check if the given file is a elf file or a macho file...
     *
     * @param path the path to the binary
     * @return the object representation
     */
    std::unique_ptr<IBinary> IBinary::parseHeader(const std::string &path) {
        std::ifstream fis(path);
        std::vector<uint8_t> magic_buffer;
        magic_buffer.resize(MAGIC_BUFF_SIZE);

        fis.read(reinterpret_cast<char *>(&magic_buffer[0]), magic_buffer.size());
        if (fis) {
            // test elf and macho
            if (Elf::isElf(magic_buffer)) {
                return std::unique_ptr<Elf>(new Elf(path));
            } // add macho here!
        }

        return std::unique_ptr<Elf>(); // throw exception!?
    }

    IBinary::IBinary(const std::string &) {
    }
}
