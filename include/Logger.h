
#ifndef OPEN_JSON_LOGGER_H
#define OPEN_JSON_LOGGER_H

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "boost/thread.hpp"
#include "CommonDef.h"


namespace open_json {

#define LOGGER Logger::GetLogger()

    class Logger final {

    private:
        MAKE_STATIC(Logger)

        static boost::once_flag m_onceFlag;

        // create a logger with 2 targets, (optionally with different log levels and formats).
        static void Init() noexcept {
            spdlog::init_thread_pool(SPDLOG_ASYNC_QUEUE_SIZE,
                                     SPDLOG_ASYNC_THREAD_COUNT); // queue with 8k items and 1 backing thread.
            auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(LOG_FILE_NAME,
                                                                                        MAX_FILE_SIZE_IN_BYTE,
                                                                                        MAX_FILES_TO_KEEP);
            std::vector<spdlog::sink_ptr> sinks{stdout_sink, rotating_sink};
            auto logger = std::make_shared<spdlog::async_logger>(LOGGER_NAME, sinks.begin(), sinks.end(),
                                                                 spdlog::thread_pool(),
                                                                 spdlog::async_overflow_policy::block);
            spdlog::register_logger(logger);
        }

    public:
        static std::shared_ptr<spdlog::logger> GetLogger() {
            boost::call_once(Init, m_onceFlag);
            return spdlog::get(LOG_FILE_NAME);
        }
    };

    boost::once_flag Logger::m_onceFlag = BOOST_ONCE_INIT;
}


#endif //OPEN_JSON_LOGGER_H
