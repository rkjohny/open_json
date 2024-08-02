#ifndef OPEN_JSON_UTILS_H
#define OPEN_JSON_UTILS_H

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>
#include <string>
#include <regex>
#include "CommonDef.h"

namespace open_json {

class Utils {
private:
    MAKE_STATIC(Utils);

public:
    static std::string Demangle(const char *mangled_name) {
        int status = 0;
        std::unique_ptr<char, void (*)(void *)> res{
                abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status),
                std::free
        };
        return (status == 0) ? res.get() : mangled_name;
    }

    static std::string CleanString(std::string &str) {
        // Regular expression to match backslashes and double quotes
        std::regex re(R"([\\"])");

        // Replace all matches with an empty string
        std::string cleaned_str = std::regex_replace(str, re, "");
        return cleaned_str;
    }

    static std::string CleanString(std::string &&str) {
        // Regular expression to match backslashes and double quotes
        std::regex re(R"([\\"])");

        // Replace all matches with an empty string
        std::string cleaned_str = std::regex_replace(str, re, "");
        return cleaned_str;
    }
};
}

#endif //OPEN_JSON_UTILS_H
