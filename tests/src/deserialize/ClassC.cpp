#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"

namespace open_json_test::serialize {

    class DeserializeClassC {
    private:
        int id = 100;
        std::string name = "Rezaul karim";

    public:
        int GetId() const {
            return id;
        }

        const std::string &GetName() const {
            return name;
        }

        void SetId(int &id) {
            this->id = id;
        }

        void SetName(std::string name) {
            this->name = name;
        }

        static constexpr std::tuple setters = std::make_tuple(
                open_json::Setter<DeserializeClassC, int &>(&DeserializeClassC::SetId, "id"),
                open_json::Setter<DeserializeClassC, std::string>(&DeserializeClassC::SetName, "name")
        );
    };

    TEST(DeserializeClassC, Test) {
        nlohmann::json jsonObject = nlohmann::json::object();
        jsonObject["id"] = 300;
        jsonObject["name"] = "David Backham";

        DeserializeClassC c = open_json::FromJson<DeserializeClassC>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), c.GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(c.GetName()));

        DeserializeClassC *p = open_json::FromJson<DeserializeClassC*>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), p->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare(p->GetName()));
        delete p;

        DeserializeClassC **pp = open_json::FromJson<DeserializeClassC**>(jsonObject);
        ASSERT_EQ(jsonObject.at("id").template get<int>(), (*pp)->GetId());
        ASSERT_EQ(0, jsonObject.at("name").template get<std::string>().compare((*pp)->GetName()));
        delete *pp;
        delete pp;
    }
}