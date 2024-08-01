#ifndef OPEN_JSON_UTILS_H
#define OPEN_JSON_UTILS_H

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>

namespace open_json {

class Utils {
public:
    static std::string demangle(const char *mangled_name) {
        int status = 0;
        std::unique_ptr<char, void (*)(void *)> res{
                abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status),
                std::free
        };
        return (status == 0) ? res.get() : mangled_name;
    }
};
}

#endif //OPEN_JSON_UTILS_H
