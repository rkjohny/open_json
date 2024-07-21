#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "../../include/open_json.h"


// deserializing an object containing another object
namespace open_json {

    class ClassA {
    private:
        int id;
        std::string name;

    public:
        ClassA() = default;
        virtual ~ClassA() = default;

        ClassA(int id, std::string name) : id{id}, name{name} {
        }

        int GetId() const {
            return id;
        }

        const std::string &GetName() const {
            return name;
        }

        REGISTER_GETTER_START
        GETTER(ClassA, int, "id", &ClassA::GetId),
        GETTER(ClassA, const std::string&, "name", &ClassA::GetName)
        REGISTER_GETTER_END
    };

    class ClassB {
    private:
        ClassA m_obj;
        ClassA *m_objPtr;
        std::vector<ClassA> m_vecObj;
        std::vector<ClassA *> *m_vecObjPtr;

    public:
        ClassB() {
            m_obj = ClassA(2, "object2");
            m_objPtr = new ClassA(3, "object3");
            m_vecObj.push_back(ClassA(4, "object4"));
            m_vecObj.push_back(ClassA(5, "object5"));
            m_vecObj.push_back(ClassA(6, "object6"));
            m_vecObjPtr = new std::vector<ClassA *>();
            m_vecObjPtr->push_back(new ClassA(7, "object7"));
            m_vecObjPtr->push_back(new ClassA(8, "object8"));
            m_vecObjPtr->push_back(new ClassA(9, "object9"));
        }

        virtual ~ClassB() {
            delete m_objPtr;
            for (auto p: *m_vecObjPtr) {
                if (p) {
                    delete p;
                }
            }
            delete m_vecObjPtr;
        }
        
        const ClassA &GetObject() const {
            return m_obj;
        }

        const ClassA *GetObjectPtr() const {
            return m_objPtr;
        }

        const std::vector <ClassA> &GetVector() const {
            return m_vecObj;
        }

        const std::vector<ClassA *> *GetVectorPtr() const {
            return m_vecObjPtr;
        }

        // will be ignored in json object
        const ClassA *GetNullPtrObject() const {
            return nullptr;
        }

        // will be ignored in json object
        const int *GetNullPtrInt() const {
            return nullptr;
        }

        REGISTER_GETTER_START
        GETTER(ClassB, const ClassA&, "object", &ClassB::GetObject),
        GETTER(ClassB, const ClassA*, "object_ptr", &ClassB::GetObjectPtr),
        GETTER(ClassB, const std::vector <ClassA>&, "vector", &ClassB::GetVector),
        GETTER(ClassB, const std::vector<ClassA *>*, "vector_ptr", &ClassB::GetVectorPtr),
        GETTER(ClassB, const ClassA*, "null_object_ptr", &ClassB::GetNullPtrObject), // will be ignored
        GETTER(ClassB, const int*, "null_int_ptr", &ClassB::GetNullPtrInt) // will be ignored
        REGISTER_GETTER_END
    };

    class ClassC {
    private:
        ClassB *objectB;

    public:
        ClassC() {
            objectB = new ClassB();
        }

        virtual ~ClassC() {
            delete objectB;
        }

        const ClassB *GetObject() const {
            return objectB;
        }

        REGISTER_GETTER_START
        GETTER(ClassC, const ClassB*, "object", &ClassC::GetObject)
        REGISTER_GETTER_END
    };

    class SerializeNestedObjectTest : public ::testing::Test {
    public:
        ClassA *objectA;
        ClassB *objectB;
        ClassC *objectC;

        void SetUp() override {
            objectA = new ClassA(1, "object1");
            objectB = new ClassB();
            objectC = new ClassC();
        }

        void TearDown() override {
            delete objectA;
            delete objectB;
            delete objectC;
        }

        static void VerifyClassA(const ClassA &obj, const nlohmann::json &jsonObject) {
            ASSERT_TRUE(jsonObject.is_object());
            ASSERT_EQ(obj.GetId(), jsonObject.at("id").template get<int>());
            ASSERT_EQ(0, obj.GetName().compare(jsonObject.at("name").template get<std::string>()));
        }

        static void VerifyClassB(const ClassB &obj, const nlohmann::json &jsonObject) {
            ASSERT_TRUE(jsonObject.is_object());
            VerifyClassA(obj.GetObject(), jsonObject.at("object"));
            VerifyClassA(*obj.GetObjectPtr(), jsonObject.at("object_ptr"));

            const nlohmann::json &jsonVec = jsonObject.at("vector");
            ASSERT_TRUE(jsonVec.is_array());
            ASSERT_TRUE(jsonVec.size() == obj.GetVector().size());
            auto itr = obj.GetVector().begin();
            for (auto &arrItem: jsonVec) {
                VerifyClassA(*itr, arrItem);
                ++itr;
            }

            const nlohmann::json &jsonVecPtr = jsonObject.at("vector_ptr");
            ASSERT_TRUE(jsonVecPtr.is_array());
            ASSERT_TRUE(jsonVecPtr.size() == obj.GetVectorPtr()->size());
            auto itrp = obj.GetVectorPtr()->begin();
            for (auto &arrItem: jsonVecPtr) {
                VerifyClassA(**itrp, arrItem);
                ++itrp;
            }
        }

        static void VerifyClassC(const ClassC &obj, const nlohmann::json &jsonObject) {
            ASSERT_TRUE(jsonObject.is_object());
            VerifyClassB(*obj.GetObject(), jsonObject.at("object"));
        }
    };

    TEST_F(SerializeNestedObjectTest, SimpleObject) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(std::move(*objectA));
        VerifyClassA(*objectA, jsonObject);

        jsonObject = open_json::ToJson(*objectA);
        VerifyClassA(*objectA, jsonObject);

        jsonObject = open_json::ToJson(objectA);
        VerifyClassA(*objectA, jsonObject);

    }

    TEST_F(SerializeNestedObjectTest, NestedObject) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(std::move(*objectB));
        VerifyClassB(*objectB, jsonObject);

        jsonObject = open_json::ToJson(*objectB);
        VerifyClassB(*objectB, jsonObject);

        jsonObject = open_json::ToJson(objectB);
        VerifyClassB(*objectB, jsonObject);
    }

    TEST_F(SerializeNestedObjectTest, NestedObject2) {
        nlohmann::json jsonObject;

        jsonObject = open_json::ToJson(std::move(*objectC));
        VerifyClassC(*objectC, jsonObject);

        jsonObject = open_json::ToJson(*objectC);
        VerifyClassC(*objectC, jsonObject);

        jsonObject = open_json::ToJson(objectC);
        VerifyClassC(*objectC, jsonObject);
    }

}