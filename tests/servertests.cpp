#include <gtest/gtest.h>
#include <thread>

#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

#include "log.h"
#include "server.hpp"

#include "database_mock.hpp"

struct ServerTestNoDatabase : public ::testing::Test {
    mlb::server::Server s;

    void SetUp() override {
        _serverThread = std::thread([this]() { s.start(); });
    }

    void TearDown() override {
        s.stop();
        _serverThread.join();
    }

    std::thread _serverThread;
};

TEST_F(ServerTestNoDatabase, positive_simple_start_stop) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    s.stop();
}

TEST_F(ServerTestNoDatabase, positive_ping) {
    curlpp::Easy request;
    request.setOpt<curlpp::options::Url>("http://localhost:9080/mlb/ping");

    request.perform();
    EXPECT_EQ(curlpp::infos::ResponseCode::get(request), 200l);
}

TEST_F(ServerTestNoDatabase, negative_get_all_players_no_database_impl_set) {
    curlpp::Easy request;
    request.setOpt<curlpp::options::Url>(
        "http://localhost:9080/mlb/player/all");
    request.perform();
    EXPECT_NE(curlpp::infos::ResponseCode::get(request), 200);
}

struct ServerTest : public ServerTestNoDatabase {
    void SetUp() override {
        s.setDatabaseImpl(db);
        ServerTestNoDatabase::SetUp();
    }

    void TearDown() override { ServerTestNoDatabase::TearDown(); }

    DatabaseMock db;
};

TEST_F(ServerTest, get_all_players) {
    mlb::data::Players players{{"Kenny", "Smith", "100"},
                               {"LeBron", "James", "101"}};
    EXPECT_CALL(db, allPlayers()).WillOnce(::testing::Return(players));

    curlpp::Easy request;
    request.setOpt<curlpp::options::Url>(
        "http://localhost:9080/mlb/player/all");
    std::ostringstream os;
    curlpp::options::WriteStream ws(&os);
    request.setOpt(ws);
    request.perform();
    EXPECT_EQ(curlpp::infos::ResponseCode::get(request), 200);
}

int main(int argc, char *argv[]) {
    setupLogger();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
