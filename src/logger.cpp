#include "log.h"

std::shared_ptr<spdlog::logger> kDefaultLogger;

namespace {

auto createLogger(bool useStdOut) {
    using namespace spdlog;
    std::vector<sink_ptr> sinks{
        std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>(),
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>("mlbserver.out",
                                                               1024 * 1024, 5),
        std::make_shared<spdlog::sinks::daily_file_sink_mt>("mlbserver.out", 23,
                                                            59)};

    auto lg = std::make_shared<logger>("mlb-server", std::begin(sinks),
                                       std::end(sinks));
    lg->set_pattern("[%D %T] [p:%P t:%t] %n[%l] %v");
    return lg;
}
} // namespace

void setupLogger(bool verbose) {
    kDefaultLogger = createLogger(verbose);
    if (verbose) {
        kDefaultLogger->set_level(spdlog::level::debug);
    }
}

void setupLogger() {
    using namespace spdlog;

    auto env = std::getenv("MLB_SERVER_LOG_LEVEL");

    if (env) {
        kDefaultLogger = createLogger(true);
        kDefaultLogger->set_level(spdlog::level::from_str(std::string{env}));
    } else {
        kDefaultLogger = createLogger(false);
        kDefaultLogger->set_level(spdlog::level::off);
    }
}
