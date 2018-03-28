#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "database_types.hpp"
#include "log.h"
#include "responseconverter.hpp"

using namespace mlb::data;

namespace fakeData {
const mlb::data::Team teamA{"Team A", 1};
const mlb::data::Team teamB{"Team B", 2};

const mlb::data::PlayerShortInfo lebron{"Lebron", "James", 10};

const mlb::data::GameReport::PlayerStatline statLine{
    lebron, 30, 10, 20, 2, 3, 5, 5, 7, 0, 7, 2, 1, 3, 4, 10};
} // namespace fakeData

TEST(JsonConverter, string) {
    auto str = "This is a test string";

    auto json = ResponseConverter::serialize(str);
    EXPECT_EQ(json, "\"This is a test string\"");
}

TEST(JsonConverter, team) {
    mlb::data::Team t1{"Team one", 10};

    const auto json = ResponseConverter::serialize(fakeData::teamA);
    const auto expected = R"({"id":1,"name":"Team A"})";

    EXPECT_EQ(json, expected);
}

TEST(JsonConverter, players) {
    mlb::data::Players p{{"asd", "asd", 10}, {"asd", "bsd", 20}};

    const auto json = ResponseConverter::serialize(p);
    const auto expected =
        R"([{"firstName":"asd","id":10,"lastName":"asd"},{"firstName":"asd","id":20,"lastName":"bsd"}])";

    EXPECT_EQ(json, expected);
}

TEST(JsonConverter, one_game) {
    mlb::data::Game p;
    p.datetime = "2012-10-12 15:00";
    p.host = fakeData::teamA;
    p.guest = fakeData::teamB;
    p.score = "54:10";

    const auto json = ResponseConverter::serialize(p);
    const auto expected =
        R"({"datetime":"2012-10-12 15:00","guest":{"id":2,"name":"Team B"},"host":{"id":1,"name":"Team A"},"score":"54:10"})";

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
    p.host = fakeData::teamA;
    p.guest = fakeData::teamB;
    p.score = "54:10";
    mlb::data::Weeks w{{10, {p}}};

    const auto json = ResponseConverter::serialize(w);
    EXPECT_NE(json, "null");
}
TEST(JsonConverter, schedule) {
    mlb::data::Game p;
    p.datetime = "2012-10-12 15:00";
    p.host = fakeData::teamA;
    p.guest = fakeData::teamB;
    p.score = "54:10";
    mlb::data::Weeks w{{10, {p}}};
    mlb::data::Schedule schedule{{w}};

    const auto json = ResponseConverter::serialize(schedule);
    EXPECT_NE(json, "null");
}

TEST(JsonConverter, playerShortInfo) {
    mlb::data::PlayerShortInfo p{"asd", "asd", 10};

    const auto json = ResponseConverter::serialize(p);
    const auto expected = R"({"firstName":"asd","id":10,"lastName":"asd"})";

    EXPECT_EQ(json, expected);
}

TEST(JsonConverter, gameReport) {
    mlb::data::GameReport gr{10,
                             fakeData::teamA,
                             fakeData::teamB,
                             {{"11:10", "20:15", "30:20", "40:30"}},
                             // host stats
                             {{fakeData::statLine, fakeData::statLine}},
                             // guestStats
                             {{fakeData::statLine, fakeData::statLine}}};
    auto js = nlohmann::json::parse(ResponseConverter::serialize(gr));
    EXPECT_EQ(js["id"], gr.id);
    EXPECT_EQ(js["host"]["id"], gr.host.id);
    EXPECT_EQ(js["scores"].get<decltype(gr.scores)>(), gr.scores);
}

TEST(JsonConverter, comment) {
    using namespace date;
    Comment cmt{10, User{"A", "B"}, "this is a test comment",
                2015_y / mar / 22};

    EXPECT_EQ("{\"id\":10,\"text\":\"this is a test "
              "comment\",\"user\":{\"firstName\":\"A\",\"lastName\":\"B\"}}",
              ResponseConverter::serialize(cmt));
}

int main(int argc, char *argv[]) {
    setupLogger();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
