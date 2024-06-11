#ifndef OPEN_JSON_STRINGUTILS_H
#define OPEN_JSON_STRINGUTILS_H

#include "CommonDef.h"
#include "string"
#include "vector"

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

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
        static void Trim(std::string &str) {
            boost::algorithm::trim_left_if(str, boost::algorithm::is_any_of("\r\n\t "));
            boost::algorithm::trim_right_if(str, boost::algorithm::is_any_of("\r\n\t "));
        }

        static void Tokenize(std::vector<std::string> &v, const std::string &str, const std::string &token) {
            boost::algorithm::split(v, str, boost::algorithm::is_any_of(token), boost::algorithm::token_compress_on);
        }

        static std::string GetNewLineStr() {
            return cm_newLineStr;
        }

        static std::string GetTabLineStr() {
            return cm_tabStr;
        }

        static void ToLower(std::string &str) {
            boost::algorithm::to_lower(str);
        }

        static void ToUpper(std::string &str) {
            boost::algorithm::to_upper(str);
        }

        static int Compare(const std::string &first, const std::string &second, bool ignore_case = false) {
            if (ignore_case) {
                return boost::algorithm::iequals(first, second);
            }
            return boost::algorithm::equals(first, second);
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
