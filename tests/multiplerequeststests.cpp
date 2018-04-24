#include <future>
#include <gtest/gtest.h>
#include <thread>

#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

#include "log.h"
#include "server.hpp"

#include "database_mock.hpp"

auto threadedGet(const std::string &url) {
    using curlpp::infos::ResponseCode;

    auto future = std::async(std::launch::async, [url]() {
        curlpp::Easy request;
        request.setOpt<curlpp::options::Url>(url);
        std::ostringstream os;
        curlpp::options::WriteStream ws(&os);
        request.setOpt(ws);
        request.perform();
        return std::make_tuple(ResponseCode::get(request), os.str());
    });

    return future;
}

struct MutlipleRequestsTest : public ::testing::Test {

    void SetUp() override {
        s.setDatabaseImpl(db);
        _serverThread = std::thread([this]() { s.start(); });
        while (!s.isRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void TearDown() override {
        s.stop();
        _serverThread.join();
    }

    mlb::server::Server s;
    std::thread _serverThread;
    DatabaseMock db;
};

TEST_F(MutlipleRequestsTest, two_requests) {
    mlb::data::Players players{{"Kenny", "Smith", 100},
                               {"LeBron", "James", 101}};
    mlb::data::ArticleHeaders articles{
        {0, "Title", "", "2018-12-10", 10, "Lady Gaga"}};
    EXPECT_CALL(db, allPlayers()).WillOnce(::testing::Invoke([&players]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return players;
    }));
    EXPECT_CALL(db, articleHeaders()).WillOnce(::testing::Invoke([&articles]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return articles;
    }));
    auto firstReq = threadedGet("http://localhost:9080/mlb/player");
    auto secondReq = threadedGet("http://localhost:9080/mlb/articleHeaders");

    EXPECT_EQ(std::get<0>(firstReq.get()), 200);
    EXPECT_EQ(std::get<0>(secondReq.get()), 200);
}

int main(int argc, char *argv[]) {
    setupLogger();
    kDefaultLogger->set_pattern("%t %v");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
