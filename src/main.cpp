#include "database.hpp"
#include "databaseimpl.hpp"
#include "log.h"
#include "server.hpp"

#include <cxxopts.hpp>

int main(int argc, const char **argv) {

    cxxopts::Options opts{"mlb-server", "REST server for MLB"};

    opts.add_options()("v,verbose", "Enable verbose mode")("h,help",
                                                           "Show help");

    const auto result = opts.parse(argc, argv);

    if (result.count("h")) {
        std::cout << opts.help({""}) << std::endl;
        return EXIT_SUCCESS;
    }

    setupLogger(result.count("d") != 0);

    mlb::data::DatabaseImpl db;

    mlb::server::Server s;
    s.setDatabaseImpl(db);
    s.start();
    return 0;
}
