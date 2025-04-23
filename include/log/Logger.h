//
// Created by horeb on 25-4-18.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/sink.h>

#include <memory>
#include <vector>

#define LOG_T(...) udc::GetLoggerInstance()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define LOG_D(...) udc::GetLoggerInstance()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::debug, __VA_ARGS__)
#define LOG_I(...) udc::GetLoggerInstance()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define LOG_W(...) udc::GetLoggerInstance()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define LOG_E(...) udc::GetLoggerInstance()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
#define LOG_F(...) udc::GetLoggerInstance()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)

namespace udc {

#define LOG_PATTERN "%^%Y-%m-%d %H:%M:%S.%e [%1!L] [%20s:%-4#] - %v%$"

inline std::shared_ptr<spdlog::logger>& GetLoggerInstance() {
    static std::shared_ptr<spdlog::logger> logger = []() {
        const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern(LOG_PATTERN);

        const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/app.log", true);
        file_sink->set_pattern(LOG_PATTERN);

        std::vector<spdlog::sink_ptr> sinks { console_sink, file_sink };
        auto combined_logger = std::make_shared<spdlog::logger>("MAIN_LOGGER", sinks.begin(), sinks.end());

        combined_logger->set_level(spdlog::level::trace);
        spdlog::register_logger(combined_logger);

        return combined_logger;
    }();
    return logger;
}

}


#endif //LOGGER_H
