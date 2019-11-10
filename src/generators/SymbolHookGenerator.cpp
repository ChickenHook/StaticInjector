//
// Created by Sascha Roth on 10.11.19.
//

#include "SymbolHookGenerator.h"

#include "tools/LoggingCallback.h"



namespace ChickenHook {

// some code snippets to inject

    constexpr const char *cppProlog("#include <string>\n"
                                    "#include <unistd.h>\n"
                                    "#include <dlfcn.h>\n"
                                    "\n"
                                    "#include \"symbolhook.h\"\n"
                                    "\n"
                                    "void *handle;\n"
                                    "\n"
                                    "void funA() {\n"
                                    "    printf(\"!WARNING!, SYMBOL HOOK CALLED BEFORE RELOCATION INSTALLED\\n\");\n"
                                    "}");

    constexpr const char *symbolAddrPart1(
            "extern \"C\" __attribute__((used)) void *");// place after this string the symbol variable name
    constexpr const char *symbolAddrPart2(" = (void *) funA;");

    constexpr const char *symbolPart1("extern \"C\" void "); // place symbol name here
    constexpr const char *symbolPart2("() {\n"
                                      "    SYMBOL_HOOK( "); // place symbol variable here
    constexpr const char *symbolPart3(");\n"
                                      "}");

    constexpr const char *dlopenPart1(
            "static void __attribute__  ((constructor (103))) hookInit() {\n");
    constexpr const char *dlopenPart2("handle = dlopen(\""); // add library name here
    constexpr const char *dlopenPart3("\", RTLD_LAZY);\n"); // add dlsym after this line
    constexpr const char *dlopenPart4("\n"
                                      "}");

    constexpr const char *dlsymPart1(
            " = dlsym(handle, \""); // symbol variable before this string, add symbol after this string
    constexpr const char *dlsymPart2("\");\n");


    SymbolHookGenerator::SymbolHookGenerator() : _os() {

    }

    bool SymbolHookGenerator::open(const std::string &file) {
        _os.open(file);
        return _os.good();
    }

    void SymbolHookGenerator::addSymbol(const std::string &symbol) {
        /*for (auto _symbol : _symbols) { // check if symbol is already added
            if (_symbol.compare(symbol) == 0) {
                log("addSymbol [-] symbol <%s> already added, skipping...");
                return;
            }
        }*/
        _symbols.insert(symbol);

    }

    void SymbolHookGenerator::apply() {
        if (_os.good()) {
            // prolog
            _os << cppProlog << std::endl;
            // vars and symbols
            for (auto symbol : _symbols) {
                _os << symbolAddrPart1 << "p_" << symbol << symbolAddrPart2 << std::endl;
                _os << symbolPart1 << symbol << symbolPart2 << "p_" << symbol << symbolPart3
                    << std::endl;
            }

            // constructor

            _os << dlopenPart1 << dlopenPart2 << _library_name << dlopenPart3;
            for (auto symbol : _symbols) {
                _os << "p_" << symbol << dlsymPart1 << symbol << dlsymPart2;
            }
            _os << dlopenPart4;
        }
    }

    void SymbolHookGenerator::close() {
        apply();
        if (_os.good()) {
            _os.close();
        }
    }

    void SymbolHookGenerator::addString(const std::string &content) {
        _os << content;
    }

    void SymbolHookGenerator::addDlOpen(const std::string &library) {
        _library_name = library;
    }

}