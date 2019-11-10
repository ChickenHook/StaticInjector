//
// Created by Sascha Roth on 03.11.19.
//

#include <tools/LoggingCallback.h>
#include "chickenHook/staticInjector/BinaryEditor.h"

namespace ChickenHook {
    std::unique_ptr<IBinary> BinaryEditor::open(const std::string &path) {
        auto header = IBinary::parseHeader(path);
        if (!(*header).open()) {
            log("BinaryEditor [-] open [-] could not open file <%s>", path.c_str());
            return nullptr;
        }
        return header;
    }

    bool BinaryEditor::close() {
        return false;
    }

    void BinaryEditor::setLoggingCallback(void (*logCallback)(const std::string &)) {
        setLogFunction(logCallback);
    }
}