#ifndef OPEN_JSON_SOFACTORY_H
#define OPEN_JSON_SOFACTORY_H

#include <mutex>

#include "CommonDef.h"
#include "Serializable.h"
#include "StringUtils.h"


namespace open_json {

#define REGISTER_CLASS(TYPE, NAME) \
    open_json::SOFactory::Register<TYPE>(NAME);

#define UNREGISTER_CLASS(TYPE, NAME) \
    opne_json::SOFactory::UnRegister<TYPE>(NAME);


#define REGISTER_CLASS_DEF(TYPE, KEY, ID) \
    private: static inline open_json::ClassRegistrar<TYPE> _class_registrar_##ID = open_json::ClassRegistrar<TYPE>( std::string(KEY) )

#define REGISTER_CLASS_DEC(TYPE, KEY, ID) \
    open_json::ClassRegistrar<TYPE> \
        TYPE::_class_registrar_##ID = open_json::ClassRegistrar<TYPE>( std::string(KEY) );


    class SOFactory final {
        MAKE_STATIC(SOFactory);

    public:

        static std::shared_ptr<Serializable> CreateObject(const std::string &key) {
            std::shared_ptr<Serializable> p = nullptr;
            std::string lwKey = key;
            StringUtils::ToLower(lwKey);

            cm_mutex.lock();
            auto itr = cm_objectCreators.find(lwKey);
            if (itr != cm_objectCreators.end()) {
                p = itr->second();
            }
            cm_mutex.unlock();

            return p;
        }

        static std::vector<std::shared_ptr<Serializable>>
        CreateObjectList(const std::string &key, const std::size_t size) {
            std::vector<std::shared_ptr<Serializable>> v;
            std::string lwKey = key;
            StringUtils::ToLower(lwKey);

            cm_mutexList.lock();
            auto itr = cm_objectListCreators.find(lwKey);
            if (itr != cm_objectListCreators.end()) {
                v = itr->second(size);
            }
            cm_mutexList.unlock();
            return v;
        }

        template<class T>
        static void Register(const std::string &key) {
            std::string lwKey = std::string(key);
            StringUtils::ToLower(lwKey);

            cm_mutex.lock();
            cm_objectCreators[lwKey] = &Create<T>;
            cm_mutex.unlock();

            cm_mutexList.lock();
            cm_objectListCreators[lwKey] = &CreateList<T>;
            cm_mutexList.unlock();
        }

        template<class T>
        static void UnRegister(const std::string &key) {
            std::string lwKey = std::string(key);
            StringUtils::ToLower(lwKey);

            cm_mutex.lock();
            auto itrObj = cm_objectCreators.find(lwKey);
            if (itrObj != cm_objectCreators.end()) {
                cm_objectCreators.erase(itrObj);
            }
            cm_mutex.unlock();


            cm_mutexList.lock();
            auto itrArr = cm_objectListCreators.find(lwKey);
            if (itrArr != cm_objectListCreators.end()) {
                cm_objectListCreators.erase(itrArr);
            }
            cm_mutexList.unlock();
        }

        static void Clear() {
            cm_mutex.lock();
            cm_objectCreators.clear();
            cm_mutex.unlock();

            cm_mutexList.lock();
            cm_objectListCreators.clear();
            cm_mutexList.unlock();
        }
    protected:
        template<class T>
        static std::shared_ptr<Serializable> Create() {
            std::shared_ptr<Serializable> ptr = std::make_shared<T>();
            return ptr;
        }

        template<class T>
        static std::vector<std::shared_ptr<Serializable>> CreateList(const size_t &size) {
            std::vector<std::shared_ptr<Serializable>> v;
            for (size_t i = 0; i < size; ++i) {
                v.push_back(std::make_shared<T>());
            }
            return v;
        }

        typedef std::shared_ptr<Serializable> (*FunPtr)(void);

        typedef std::map<std::string, FunPtr> ListCreators;

        typedef std::vector<std::shared_ptr<Serializable>> (*FunPtrArr)(const size_t&);

        typedef std::map<std::string, FunPtrArr> ListCreatorsArr;

        static inline std::mutex cm_mutex;
        static inline ListCreators cm_objectCreators;

        static inline std::mutex cm_mutexList;
        static inline ListCreatorsArr cm_objectListCreators;
    };

    template<class T>
    class ClassRegistrar {
    public:

        explicit ClassRegistrar(const std::string &key) {
            SOFactory::Register<T>(key);
        }

    protected:
        ClassRegistrar() = default;
    };
}


#endif //OPEN_JSON_SOFACTORY_H
