#include "database.hpp"
#include "databaseimpl.hpp"
#include "databaseimpldummy.hpp"
#include "log.h"
#include "server.hpp"

#include <cxxopts.hpp>

const std::string baseDummyDir{DUMMYDATA};

bool bDumpJson = false;

int main(int argc, const char **argv) {

    cxxopts::Options opts{"mlb-server", "REST server for MLB"};

    opts.add_options()("v,verbose", "Enable verbose mode")(
        "h,help", "Show help")("d,dummy", "Dummy database implementation")(
        "j,json", "Dump json to files");

    const auto result = opts.parse(argc, argv);

    if (result.count("h")) {
        std::cout << opts.help({""}) << std::endl;
        return EXIT_SUCCESS;
    }

    setupLogger(result.count("v") != 0);

    bDumpJson = result.count("j") != 0;

    mlb_server_debug("Using fake data? {}", result.count("d") != 0);
    const bool dummy = result.count("d") != 0;

    mlb::server::Server s;
    mlb::data::DatabaseImplDummy dummyImpl{baseDummyDir};
    mlb::data::DatabaseImpl db;

    if (dummy) {
        s.setDatabaseImpl(dummyImpl);
    } else {
        throw std::runtime_error("No impl yet");
        // s.setDatabaseImpl(db);
    }

    s.start();

    while (not s.isRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    mlb_server_info("Server is up and running");

    return 0;
}
