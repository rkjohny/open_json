#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "../../include/open_json.h"


namespace open_json_test {

    class PointerTestUpper {
    public:
        std::vector<std::string ***> ***m_names;

        std::vector<std::string ***> ***GetNames() const {
            return m_names;
        }

        REGISTER_GETTER_START
        GETTER(PointerTestUpper, std::vector<std::string ***>***, "names", &PointerTestUpper::GetNames)
        REGISTER_GETTER_END
    };

    class PointerTestNested {
    public:
        int ***m_id;
        PointerTestUpper ***m_upper;

        int ***GetId() const {
            return m_id;
        }

        PointerTestUpper ***GetBase() const {
            return m_upper;
        }

        REGISTER_GETTER_START
        GETTER(PointerTestNested, int***, "id", &PointerTestNested::GetId),
        GETTER(PointerTestNested, PointerTestUpper***, "upper", &PointerTestNested::GetBase)
        REGISTER_GETTER_END
    };

    static void verifyUpper(PointerTestUpper &upper, nlohmann::json &jsonUpper) {
        ASSERT_TRUE(jsonUpper.is_object());
        nlohmann::json jsonVecNames = jsonUpper.at("names");
        ASSERT_TRUE(jsonVecNames.is_array());
        auto itr = (***upper.m_names).begin();
        for (auto &jName : jsonVecNames) {
            ASSERT_EQ(0, (****itr).compare(jName));
            ++itr;
        }
    }

    static void verifyNested(PointerTestNested &nested, nlohmann::json &jsonNested) {
        verifyUpper(***nested.m_upper, jsonNested.at("upper"));
        ASSERT_EQ(***nested.m_id, jsonNested.at("id").template get<int>());
    }

    TEST(PointerTest, TestTriplePointer) {
        PointerTestUpper ***upper = new PointerTestUpper **(new PointerTestUpper*(new PointerTestUpper()));

        std::vector<std::string ***> ***names = new std::vector<std::string ***> **(new std::vector<std::string ***>*(new std::vector<std::string***>()));
        (**names)->push_back(new std::string **(new std::string*(new std::string("First String"))));
        (**names)->push_back(new std::string **(new std::string*(new std::string("Second String"))));
        (**names)->push_back(new std::string **(new std::string*(new std::string("Third String"))));
        (**upper)->m_names = names;

        nlohmann::json jsonUpper = open_json::ToJson(upper);
        verifyUpper(***upper, jsonUpper);

        PointerTestNested ***nested = new PointerTestNested **(new PointerTestNested *(new PointerTestNested()));
        (**nested)->m_id = new int ** (new int * (new int (100)));
        (**nested)->m_upper = upper;

        nlohmann::json jsonNested = open_json::ToJson(nested);
        verifyNested(***nested, jsonNested);


        for (auto name : ***(***upper).m_names) {
            delete **name;
            delete *name;
            delete name;
        }

        delete **upper;
        delete *upper;
        delete upper;

        delete **(***nested).m_id;
        delete *(***nested).m_id;
        delete (***nested).m_id;

        delete **nested;
        delete *nested;
        delete nested;
    }
}
