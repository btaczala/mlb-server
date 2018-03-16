#include "log.h"

std::shared_ptr<spdlog::logger> kDefaultLogger;

void setupLogger(bool verbose) {
    kDefaultLogger = spdlog::stdout_color_mt("cds");
    if (verbose) {
        kDefaultLogger->set_level(spdlog::level::debug);
    }
}

void setupLogger() {
    kDefaultLogger = spdlog::stdout_color_mt("cds");

    auto env = std::getenv("MLB_SERVER_LOG_LEVEL");

    if (env) {
        kDefaultLogger->set_level(spdlog::level::from_str(std::string{env}));
    } else {
        kDefaultLogger->set_level(spdlog::level::off);
    }
}
