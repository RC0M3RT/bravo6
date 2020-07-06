#include "bravo6/logging/logging.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace bravo6 {
namespace logging {

logger::logger()
    : initialized_{false}
    , spd_logger_{nullptr}
{
}

logger::~logger()
{
    B6_INFO("Shutting down logger")
    delete spd_logger_;
}

void logger::init() {

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("%^[%T] %n: %v%$");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
    file_sink->set_level(spdlog::level::trace);
    file_sink->set_pattern("[%T] [%l] %n: %v");

    spdlog::sinks_init_list sink_list = { file_sink, console_sink };

    spd_logger_ = new spdlog::logger("bravo6", sink_list.begin(), sink_list.end());
    spd_logger_->set_level(spdlog::level::trace);

    initialized_ = true;
    spd_logger_->info("Logger initialized");
}

spdlog::logger* logger::get_logger() const
{
    return spd_logger_;
}

} // namespace logging
} // namespace bravo6