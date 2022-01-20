#pragma once
#ifndef NDEBUG
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif
#include <spdlog/spdlog.h>

namespace rela{

enum class format_style{
    raw = -1,           // The style just logging the raw content, nothing else(e.g. if it is "hello", just logging "hello" )
    loc = -2,           // The sytle print filename, line, and function name
};

// Check if the style is 'loc' or not
constexpr int parse_style(int line_number, format_style style)
{
    return style == format_style::loc ? line_number : static_cast<int>(style);
}

#define LOG_LOGGER_CALL(logger, level, ...) (logger)->log(level, __VA_ARGS__)
#define LOG_LOGGER_CALLEX(logger, level, style, ...) (logger)->log(spdlog::source_loc{__FILE__, parse_style(__LINE__, style), SPDLOG_FUNCTION}, level, __VA_ARGS__)

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
#    define LOG_TRACE(...) LOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::trace, __VA_ARGS__)
#    define LOG_TRACEEX(style, ...) LOG_LOGGER_CALLEX(spdlog::default_logger_raw(), spdlog::level::trace, style, __VA_ARGS__)
#else
#    define LOG_TRACE(...) (void)0
#    define LOG_TRACEEX(style, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#    define LOG_DEBUG(...) LOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::debug, __VA_ARGS__)
#    define LOG_DEBUGEX(style, ...) LOG_LOGGER_CALLEX(spdlog::default_logger_raw(), spdlog::level::debug, style, __VA_ARGS__)
#else
#    define LOG_DEBUG(...) (void)0
#    define LOG_DEBUGEX(style, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#    define LOG_INFO(...) LOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::info, __VA_ARGS__)
#    define LOG_INFOEX(style, ...) LOG_LOGGER_CALLEX(spdlog::default_logger_raw(), spdlog::level::info, style, __VA_ARGS__)
#else
#    define LOG_INFO(...) (void)0
#    define LOG_INFOEX(style, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#    define LOG_WARN(...) LOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::warn, __VA_ARGS__)
#    define LOG_WARNEX(style, ...) LOG_LOGGER_CALLEX(spdlog::default_logger_raw(), spdlog::level::warn, style, __VA_ARGS__)
#else
#    define LOG_WARN(...) (void)0
#    define LOG_WARNEX(style, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#    define LOG_ERROR(...) LOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::err, __VA_ARGS__)
#    define LOG_ERROREX(style, ...) LOG_LOGGER_CALLEX(spdlog::default_logger_raw(), spdlog::level::err, style, __VA_ARGS__)
#else
#    define LOG_ERROR(...) (void)0
#    define LOG_ERROREX(style, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#    define LOG_CRITICAL(...) LOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::critical, __VA_ARGS__)
#    define LOG_CRITICALEX(style, ...) LOG_LOGGER_CALLEX(spdlog::default_logger_raw(), spdlog::level::critical, style, __VA_ARGS__)
#else
#    define LOG_CRITICAL(...) (void)0
#    define LOG_CRITICALEX(style, ...) (void)0
#endif

void init_log();
void cleanup_log();

}//rela