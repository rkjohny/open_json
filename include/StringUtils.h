#ifndef OPEN_JSON_STRINGUTILS_H
#define OPEN_JSON_STRINGUTILS_H

#include "CommonDef.h"
#include "string"


namespace open_json {
    class StringUtils final {
    private:
        MAKE_STATIC(StringUtils);

        static std::string cm_newLineStr;
        static std::string cm_tabStr;

        class Initializer {
        public:
            Initializer() {
                //crates new line string
                m_ss << m_ss.widen('\n');
                StringUtils::cm_newLineStr = m_ss.str();

                //clear the buffer
                m_ss.str("");

                //create tab string
                m_ss << m_ss.widen('\t');
                StringUtils::cm_tabStr = m_ss.str();
            }

        private:
            std::ostringstream m_ss;
        };

        static Initializer cm_initializer;

    public:

        static std::string GetNewLineStr() {
            return cm_newLineStr;
        }

        static std::string GetTabLineStr() {
            return cm_tabStr;
        }

        static void ToLower(std::string &str) {
            for (size_t i = 0; i<str.length(); ++i)
                str[i] = std::tolower(str[i]);
        }

        static void ToUpper(std::string &str) {
            for (size_t i = 0; i<str.length(); ++i)
                str[i] = std::toupper(str[i]);
        }
    };

    //creation of static variable,
    //note that cm_newLineStr and cm_tabStr should be created before cm_initializer, the order is important
    //because the constructor of cm_initializer will use these two variables
    std::string StringUtils::cm_newLineStr;
    std::string StringUtils::cm_tabStr;
    StringUtils::Initializer StringUtils::cm_initializer;
}


#endif //OPEN_JSON_STRINGUTILS_H
