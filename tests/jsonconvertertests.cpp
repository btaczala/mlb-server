#include <gtest/gtest.h>

#include "database_types.hpp"
#include "log.h"
#include "responseconverter.hpp"

TEST(JsonConverter, team) {
    mlb::data::Team t1{"Team one", 10};

    const auto json = ResponseConverter::serialize(t1);
    const auto expected = R"({"id":10,"name":"Team one"})";

    EXPECT_EQ(json, expected);
}

TEST(JsonConverter, players) {
    mlb::data::Players p{{"asd", "asd", 10}, {"asd", "bsd", 20}};

    const auto json = ResponseConverter::serialize(p);
    const auto expected =
        R"([{"firstname":"asd","id":10,"lastname":"asd"},{"firstname":"asd","id":20,"lastname":"bsd"}])";

    EXPECT_EQ(json, expected);
}

TEST(JsonConverter, one_game) {
    mlb::data::Game p;
    p.datetime = "2012-10-12 15:00";
    p.host = {"Team A", 10};
    p.guest = {"Team A", 10};
    p.score = "54:10";

    const auto json = ResponseConverter::serialize(p);
    const auto expected =
        R"({"datetime":"2012-10-12 15:00","guest":{"id":10,"name":"Team A"},"host":{"id":10,"name":"Team A"},"score":"54:10"})";

    EXPECT_EQ(json, expected);
}

TEST(JsonConverter, week) {
    mlb::data::Game p;
    p.datetime = "2012-10-12 15:00";
    p.host = {"Team A", 10};
    p.guest = {"Team A", 10};
    p.score = "54:10";
    mlb::data::Week w{10, {p}};

    const auto json = ResponseConverter::serialize(w);
    EXPECT_NE(json, "null");
}

TEST(JsonConverter, weeks) {
    mlb::data::Game p;
    p.datetime = "2012-10-12 15:00";
    p.host = {"Team A", 10};
    p.guest = {"Team A", 10};
    p.score = "54:10";
    mlb::data::Weeks w{{10, {p}}};

    const auto json = ResponseConverter::serialize(w);
    EXPECT_NE(json, "null");
}
TEST(JsonConverter, schedule) {
    mlb::data::Game p;
    p.datetime = "2012-10-12 15:00";
    p.host = {"Team A", 10};
    p.guest = {"Team A", 10};
    p.score = "54:10";
    mlb::data::Weeks w{{10, {p}}};
    mlb::data::Schedule schedule{{w}};

    const auto json = ResponseConverter::serialize(schedule);
    EXPECT_NE(json, "null");
}

TEST(JsonConverter, playerShortInfo) {
    mlb::data::PlayerShortInfo p{"asd", "asd", 10};

    const auto json = ResponseConverter::serialize(p);
    const auto expected = R"({"firstname":"asd","id":10,"lastname":"asd"})";

    EXPECT_EQ(json, expected);
}

int main(int argc, char *argv[]) {
    setupLogger();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
