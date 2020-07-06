#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>

namespace bravo6 {
namespace logging {

class logger{
public:

    logger(const logger&) = delete;
    logger& operator=(const logger&) = delete;
    logger(logger&&) = delete;
    logger& operator=(logger&&) = delete;

    ~logger();

    static logger& instance(){
        static logger logger_{};
        if(false == logger_.initialized_){
            logger_.init();
        }
        return logger_;
    }

    spdlog::logger* get_logger() const;

private:
    logger();
    void init();

    bool initialized_{false};
    spdlog::logger* spd_logger_;
};

} // namespace logging
} // namespace bravo6

#define B6_TRACE(...)    ::bravo6::logging::logger::instance().get_logger()->trace(__VA_ARGS__);
#define B6_DEBUG(...)    ::bravo6::logging::logger::instance().get_logger()->debug(__VA_ARGS__);
#define B6_INFO(...)    ::bravo6::logging::logger::instance().get_logger()->info(__VA_ARGS__);
#define B6_WARN(...)    ::bravo6::logging::logger::instance().get_logger()->warn(__VA_ARGS__);
#define B6_CRIT(...)    ::bravo6::logging::logger::instance().get_logger()->critical(__VA_ARGS__);