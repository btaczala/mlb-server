// clang-format off
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
// clang-format on
#include <cstring>
#include <iostream>
#include <memory>

extern std::shared_ptr<spdlog::logger> kDefaultLogger;

extern void setupLogger(bool);
extern void setupLogger();

#define __FILENAME__ \
    (std::strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define mlb_server_trace(fmt, ...)                                             \
    do {                                                                       \
        kDefaultLogger->trace("[{}():{}@{}] " fmt, __FUNCTION__, __FILENAME__, \
                              __LINE__, ##__VA_ARGS__);                        \
    } while (0)
#define mlb_server_debug(fmt, ...)                                             \
    do {                                                                       \
        kDefaultLogger->debug("[{}():{}@{}] " fmt, __FUNCTION__, __FILENAME__, \
                              __LINE__, ##__VA_ARGS__);                        \
    } while (0)
#define mlb_server_warn(fmt, ...)                                             \
    do {                                                                      \
        kDefaultLogger->warn("[{}():{}@{}] " fmt, __FUNCTION__, __FILENAME__, \
                             __LINE__, ##__VA_ARGS__);                        \
    } while (0)
#define mlb_server_error(fmt, ...)                                             \
    do {                                                                       \
        kDefaultLogger->error("[{}():{}@{}] " fmt, __FUNCTION__, __FILENAME__, \
                              __LINE__, ##__VA_ARGS__);                        \
    } while (0)
#define mlb_server_info(fmt, ...)                                             \
    do {                                                                      \
        kDefaultLogger->info("[{}():{}@{}] " fmt, __FUNCTION__, __FILENAME__, \
                             __LINE__, ##__VA_ARGS__);                        \
    } while (0)
