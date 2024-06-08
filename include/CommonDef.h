#ifndef OPEN_JSON_COMMONDEF_H
#define OPEN_JSON_COMMONDEF_H


namespace open_json {

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
