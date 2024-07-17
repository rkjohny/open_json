#ifndef OPEN_JSON_STRINGUTILS_H
#define OPEN_JSON_STRINGUTILS_H

#include "CommonDef.h"
#include "string"


namespace open_json {
    class StringUtils final {
    private:
        MAKE_STATIC(StringUtils);

    public:

        static void ToLower(std::string &str) {
            for (size_t i = 0; i<str.length(); ++i)
                str[i] = std::tolower(str[i]);
        }

        static void ToUpper(std::string &str) {
            for (size_t i = 0; i<str.length(); ++i)
                str[i] = std::toupper(str[i]);
        }
    };
}


#endif //OPEN_JSON_STRINGUTILS_H
