#include <iostream>

#include "database.hpp"
#include "server.hpp"

#include "databaseimpl.hpp"

extern void setupLogger(bool);

int main(int argc, char *argv[]) {
    setupLogger(true);
    mlb::data::DatabaseImpl db;

    mlb::server::Server s;
    s.setDatabaseImpl(db);
    s.start();
    return 0;
}
