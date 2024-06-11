#ifndef OPEN_JSON_SOFACTORY_H
#define OPEN_JSON_SOFACTORY_H

#include "CommonDef.h"
#include "AbstractSerializable.h"
#include "StringUtils.h"
#include "boost/thread.hpp"


namespace open_json {

#define REGISTER_CLASS(TYPE, NAME) \
    open_json::SOFactory::Register<TYPE>(NAME);

#define UNREGISTER_CLASS(TYPE, NAME) \
    opne_json::SOFactory::UnRegister<TYPE>(NAME);


#define REGISTER_CLASS_DEF(TYPE, KEY, ID) \
    private: static open_json::ClassRegistrar<TYPE> _class_registrar_##ID;

#define REGISTER_CLASS_DEC(TYPE, KEY, ID) \
    open_json::ClassRegistrar<TYPE> \
        TYPE::_class_registrar_##ID = open_json::ClassRegistrar<TYPE>( std::string(KEY) );


    class SOFactory final {
        MAKE_STATIC(SOFactory);

    public:

        static std::shared_ptr<AbstractSerializable> CreateObject(const std::string &key) {
            std::shared_ptr<AbstractSerializable> p = nullptr;
            std::string lwKey = key;
            StringUtils::ToLower(lwKey);

            cm_mutex.lock();
            ListCreators::iterator itr = cm_objectCreators.find(lwKey);
            if (itr != cm_objectCreators.end()) {
                p = itr->second();
            }
            cm_mutex.unlock();

            return p;
        }

        static std::vector<std::shared_ptr<AbstractSerializable>>
        CreateObjectArray(const std::string &key, const std::size_t size) {
            std::vector<std::shared_ptr<AbstractSerializable>> v;
            std::string lwKey = key;
            StringUtils::ToLower(lwKey);

            cm_mutexArr.lock();
            ListCreatorsArr::iterator itr = cm_objectArrayCreators.find(lwKey);
            if (itr != cm_objectArrayCreators.end()) {
                v = itr->second(size);
            }
            cm_mutexArr.unlock();
            return v;
        }

        template<class T>
        static void Register(const std::string &key) {
            static_assert(std::is_base_of<AbstractSerializable, T>::value,
                          "T must be derived from AbstractSerializable");
            std::string lwKey = key;
            StringUtils::ToLower(lwKey);

            cm_mutex.lock();
            cm_objectCreators[lwKey] = &Create<T>;
            cm_mutex.unlock();

            cm_mutexArr.lock();
            cm_objectArrayCreators[lwKey] = &CreateArray<T>;
            cm_mutexArr.unlock();
        }

        template<class T>
        static void UnRegister(const std::string &key) {
            static_assert(std::is_base_of<AbstractSerializable, T>::value,
                          "T must be derived from AbstractSerializable");
            std::string lwKey = key;
            StringUtils::ToLower(lwKey);

            cm_mutex.lock();
            auto itrObj = cm_objectCreators.find(lwKey);
            if (itrObj != cm_objectCreators.end()) {
                cm_objectCreators.erase(itrObj);
            }
            cm_mutex.unlock();


            cm_mutexArr.lock();
            auto itrArr = cm_objectArrayCreators.find(lwKey);
            if (itrArr != cm_objectArrayCreators.end()) {
                cm_objectArrayCreators.erase(itrArr);
            }
            cm_mutexArr.unlock();
        }

        static void Clear();

    protected:
        typedef std::shared_ptr<AbstractSerializable> (*FunPtr)(void);

        typedef std::map<std::string, FunPtr> ListCreators;

        typedef std::vector<std::shared_ptr<AbstractSerializable>> (*FunPtrArr)(const size_t&);

        typedef std::map<std::string, FunPtrArr> ListCreatorsArr;

        template<class T>
        static std::shared_ptr<AbstractSerializable> Create() {
            return std::make_shared<T>();
        }

        template<class T>
        static std::vector<std::shared_ptr<AbstractSerializable>> CreateArray(const size_t &size) {
            std::vector<std::shared_ptr<AbstractSerializable>> v;
            for (size_t i = 0; i < size; ++i) {
                v.push_back(std::make_shared<T>());
            }
            return v;
        }

        static boost::mutex cm_mutex;
        static ListCreators cm_objectCreators;

        static boost::mutex cm_mutexArr;
        static ListCreatorsArr cm_objectArrayCreators;
    };

    template<class T>
    class ClassRegistrar {
    public:

        ClassRegistrar(const std::string &key) {
            SOFactory::Register<T>(key);
        }

    protected:
        ClassRegistrar() = default;
    };

    boost::mutex SOFactory::cm_mutex;
    SOFactory::ListCreators SOFactory::cm_objectCreators;

    boost::mutex SOFactory::cm_mutexArr;
    SOFactory::ListCreatorsArr SOFactory::cm_objectArrayCreators;
}


#endif //OPEN_JSON_SOFACTORY_H
