#include "log.h"
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/pattern_formatter.h>

#ifdef _WIN32
    #define SLASH '\\'
#else
    #define SLASH '/'
#endif

static constexpr const char* get_file_name(const char* file_path)
{
    char c = '\0';
    int index = 0;
    int last_slash_index = 0;
    do
    {
        c = file_path[index];
        if (c == SLASH) last_slash_index = index;
        ++index;
    } while (c != '\0');

    return file_path + last_slash_index + 1;
}


namespace rela{

// Change the formatter style by line number
class code_formatter_flag : public spdlog::custom_flag_formatter
{
public:
    void format(const spdlog::details::log_msg & msg, const std::tm & t, spdlog::memory_buf_t &dest) override
    {
        // Get millseconds
        auto to_millseconds = [&msg] {
            using std::chrono::duration_cast;
            using std::chrono::seconds;
            auto duration = msg.time.time_since_epoch();
            auto secs = duration_cast<seconds>(duration);
            return duration_cast<std::chrono::milliseconds>(duration) - duration_cast<std::chrono::milliseconds>(secs);
        };

        // Print filename, line, and function name, format_style::loc
        if (msg.source.line > 0)
        {
            std::string code_txt = fmt::format("[{}:{}:{}.{}] [{}] [{}:{},{}] {}", t.tm_hour, t.tm_min, t.tm_sec, to_millseconds().count(), spdlog::level::to_string_view(msg.level),
                get_file_name(msg.source.filename), msg.source.line, msg.source.funcname, msg.payload);
            dest.append(code_txt.data(), code_txt.data() + code_txt.size());

        // Nomal logging, don't print filename, line, and function name
        } else if(msg.source.line == 0) {
            std::string code_txt = fmt::format("[{}:{}:{}.{}] [{}] {}", t.tm_hour, t.tm_min, t.tm_sec, to_millseconds().count(), spdlog::level::to_string_view(msg.level),
                    msg.payload);
                dest.append(code_txt.data(), code_txt.data() + code_txt.size());

        // else custom style
        } else {
            auto style = static_cast<format_style>(msg.source.line);

            switch (style)
            {
            // Just print raw content
            case format_style::raw:
            {
                std::string code_txt = fmt::format("{}", msg.payload);
                dest.append(code_txt.data(), code_txt.data() + code_txt.size());
                break;
            }
            
            default:
                throw std::runtime_error("Wrong format_style value! Please check the input line number");
            }
        }
    }

    std::unique_ptr<custom_flag_formatter> clone() const override
    {
        return spdlog::details::make_unique<code_formatter_flag>();
    }
};

void init_log()
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::trace);
#else
    spdlog::set_level(spdlog::level::info);
#endif
    auto file_logger = spdlog::basic_logger_mt<spdlog::async_factory>
        ("file_logger", "logs/logger.txt");

    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<code_formatter_flag>('*').set_pattern("%*");
    file_logger->set_formatter(std::move(formatter));

    spdlog::set_default_logger(file_logger);
    LOG_INFOEX(format_style::raw, "--------------------------------------------------------");
    LOG_INFO("Starting log");
}

void cleanup_log()
{
    LOG_INFO("Log shutdown");
    LOG_INFOEX(format_style::raw, "--------------------------------------------------------\n\n\n");
    spdlog::shutdown();
}

}//rela