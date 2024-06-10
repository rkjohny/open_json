#ifndef OPEN_JSON_COMMONDEF_H
#define OPEN_JSON_COMMONDEF_H


namespace open_json {


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    //define something for Windows (32-bit and 64-bit, this part is common)
#   define WINDOWS
#   if defined (_WIN64) || defined(__x86_64__) || defined(_M_X64)
        //define something for Windows (64-bit only)
#       define WINDOWS64
#   elif defined(__i386) || defined(_M_IX86)
        //define something for Windows (32-bit only)
#       define WINDOWS32
#   else
#       error "Unknown Windows architecture."
#   endif
#elif __APPLE__
    #include <TargetConditionals.h>
#   if TARGET_OS_SIMULATOR
        // Generated code will run under iOS, tvOS, or watchOS Simulator
#   elif TARGET_OS_MACCATALYST
        // Mac's Catalyst (ports iOS API into Mac, like UIKit).
#   elif TARGET_OS_BRIDGE
        // Generated code will run under Bridge devices
#   elif TARGET_OS_IPHONE
        // Generated code will run under iOS iOS, tvOS, or watchOS device
#   elif TARGET_OS_OSX
        // Generated code will run under OS X devices
#       define APPLE
#   elif TARGET_OS_MAC
        // Other kinds of Apple platforms
#   else
#       error "Unknown Apple platform"
#   endif
#elif __ANDROID__
    // Below __linux__ check should be enough to handle Android,
    // but something may be unique to Android.
#elif __linux__
    // linux
#   define LINUX
#elif __unix__ // all unices not caught above
    // Unix
#   define UNIX
#elif defined(_POSIX_VERSION)
    // POSIX
#   define POSIX
#else
#   error "Unknown compiler"
#endif



#ifdef __SIZEOF_POINTER__
#   if __SIZEOF_POINTER__ == 8
        // 64 bit
#       define OS_64_BIT
#       define WORD_SIZE 64
#   elif __SIZEOF_POINTER__ == 4
        // 32 bit
#       define OS_32_BIT
#       define WORD_SIZE 32
#   else
#       error "Unknown pointer size."
#   endif
#endif


#ifdef BUILDING_OPEN_JSON_LIB
#define OPEN_JSON_API __declspec(dllexport)
#else
#define OPEN_JSON_API __declspec(dllimport)
#endif


#define MAX_FILE_SIZE_IN_BYTE  (2 * 1024 * 1024) /* 2 MB */
#define MAX_FILES_TO_KEEP  10
#define LOG_FILE_NAME "log/open_json.log"
#define LOGGER_NAME "open_json_logger"
#define SPDLOG_ASYNC_QUEUE_SIZE (8 * 1024) /* 8KB */
#define SPDLOG_ASYNC_THREAD_COUNT 1


#define MAKE_STATIC(TYPE) \
    TYPE() = delete; \
    ~TYPE() = delete;


}
#endif //OPEN_JSON_COMMONDEF_H
