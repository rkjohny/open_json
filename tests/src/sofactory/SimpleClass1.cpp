#include <gtest/gtest.h>
#include <string>
#include "../../../include/open_json.h"
#include "../../include/RandomGenerator.h"

namespace open_json_test::so_factory::simple_class_1 {

    const std::string SO_FACTORY_SIMPLE_CLASS_1 = "open_json_test::so_factory::simple_class_1::simple_class_1";

    class SimpleClass1 : public open_json::Serializable {
    private:
        int id = 100;
        std::string name = "Rezaul karim";

        //REGISTER_CLASS_DEF(SimpleClass1, SO_FACTORY_SIMPLE_CLASS_1, 0);

    public:
        int GetId() const {
            return id;
        }

        void SetId(int id) {
            this->id = id;
        }

        const std::string &GetName() const {
            return name;
        }

        void SetName(std::string name) {
            this->name = name;
        }

        REGISTER_GETTER_START
        GETTER(SimpleClass1, int, "id", &SimpleClass1::GetId),
        GETTER(SimpleClass1, const std::string&, "name", &SimpleClass1::GetName)
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        SETTER(SimpleClass1, int, "id", &SimpleClass1::SetId),
        SETTER(SimpleClass1, std::string, "name", &SimpleClass1::SetName)
        REGISTER_SETTER_END
    };

    TEST(so_factory_SimpleClass1, ObjectTest) {
        REGISTER_CLASS(SimpleClass1, SO_FACTORY_SIMPLE_CLASS_1);

        std::shared_ptr<open_json::Serializable> ptr = open_json::SOFactory::CreateObject(SO_FACTORY_SIMPLE_CLASS_1);

        SimpleClass1 *p = dynamic_cast<SimpleClass1*>(ptr.get());

        p->SetName("Rezaul Karim");
        p->SetId(100);

        nlohmann::json jsonObject = open_json::ToJson(p);
        ASSERT_EQ(p->GetId(), jsonObject.at("id").template get<int>());
        ASSERT_EQ(0, p->GetName().compare(jsonObject.at("name").template get<std::string>()));

        SimpleClass1 a = open_json::FromJson<SimpleClass1>(jsonObject);

        ASSERT_EQ(p->GetId(), a.GetId());
        ASSERT_EQ(0, p->GetName().compare(a.GetName()));
    }

    TEST(so_factory_SimpleClass1, VectorTest) {
        REGISTER_CLASS(SimpleClass1, SO_FACTORY_SIMPLE_CLASS_1);

        std::vector<std::shared_ptr<open_json::Serializable>> ptrVec = open_json::SOFactory::CreateObjectList(SO_FACTORY_SIMPLE_CLASS_1, 3);

        for (auto ptr : ptrVec) {
            SimpleClass1 *p = dynamic_cast<SimpleClass1*>(ptr.get());

            p->SetName(open_json_test::RandomGenerator::GetInstance().GetNextString(10));
            p->SetId(open_json_test::RandomGenerator::GetInstance().GetNextInt());

            nlohmann::json jsonObject = open_json::ToJson(p);
            ASSERT_EQ(p->GetId(), jsonObject.at("id").template get<int>());
            ASSERT_EQ(0, p->GetName().compare(jsonObject.at("name").template get<std::string>()));

            SimpleClass1 a = open_json::FromJson<SimpleClass1>(jsonObject);

            ASSERT_EQ(p->GetId(), a.GetId());
            ASSERT_EQ(0, p->GetName().compare(a.GetName()));
        }
    }
}