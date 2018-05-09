#include "databaseimpldummy.hpp"
#include <experimental/filesystem>
#include <fstream>
#include <random>

#include <nlohmann/json.hpp>

#include "log.h"

namespace fs = std::experimental::filesystem;

namespace __fakeData {
const mlb::data::Players allPlayers{// clang-format off
    {"Bartek", "Taczała ", 0},
    {"Michael", "Jordan", 0},
    {"Scottie", "Pippen", 0},
    {"Kevin", "Love", 0}};
// clang-format on

const mlb::data::ArticleHeaders allHeaders{{0, "This is a title",
                                            "This is a simple text",
                                            "2018-10-15", 0, "Bartek", ""}};

std::string readfile(const fs::path &path) {
    std::ifstream fileToRead{path.c_str()};
    fileToRead >> std::noskipws;

    return std::string{std::istream_iterator<char>(fileToRead),
                       std::istream_iterator<char>()};
}

nlohmann::json readJson(const fs::path &path) {
    return nlohmann::json::parse(readfile(path));
}
template <typename T>
auto randomValue(T &&container, int number = 1) {
    using Val = typename std::decay_t<T>::value_type;
    std::vector<Val> vv;
    std::sample(std::begin(container), std::end(container),
                std::back_inserter(vv), number,
                std::mt19937{std::random_device{}()});

    return vv.at(0);
}
using namespace mlb::data;
const std::vector<Team> teams{Team{"RIM", 0}, Team{"FRASSATI", 1},
                              Team{"OPEN FINANCE", 2}};

const std::vector<std::string> scores{"44:33", "22:11", "56:70", ""};
const std::vector<std::string> dates{"2018-10-15"};

} // namespace __fakeData

namespace mlb {
namespace data {
DatabaseImplDummy::DatabaseImplDummy(const std::string &baseDummyDir)
    : _rootDir(baseDummyDir) {
    mlb_server_debug("{} {}", baseDummyDir, _rootDir);
}

Players DatabaseImplDummy::allPlayers() const { return __fakeData::allPlayers; }

ArticleHeaders DatabaseImplDummy::articleHeaders() const {
    const fs::path articleDirPath = fs::path{_rootDir} / fs::path{"articles"};

    mlb_server_debug("{}", articleDirPath.string());

    auto readArticle = [](const fs::path &filepath) {
        const auto json = __fakeData::readJson(filepath);

        mlb_server_debug("Reading article from path {}", filepath.string());

        std::string text = json["text"];

        if (text.size() > 260) {
            text.erase(260, std::string::npos);
            text += "[...]";
        }

        return ArticleHeader{json["id"],
                             json["title"],
                             text,
                             json["postedDate"],
                             json["numberOfComments"],
                             json["author"],
                             json["picture"].get<std::string>()};
    };

    ArticleHeaders arts;

    auto it = fs::directory_iterator(articleDirPath);

    std::transform(it, fs::directory_iterator(), std::back_inserter(arts),
                   [&readArticle](const fs::path &filepath) -> ArticleHeader {
                       return readArticle(filepath);
                   });
    return arts;
}

std::optional<ArticleHeader>
DatabaseImplDummy::article(std::uint32_t id) const {
    const fs::path articlePath =
        fs::path{_rootDir} / fs::path{"articles"} /
        fs::path{std::to_string(id) + std::string{".json"}};

    mlb_server_debug("Reading file {}", articlePath.string());

    if (fs::exists(articlePath)) {
        const auto json = __fakeData::readJson(articlePath);
        return ArticleHeader{json["id"],
                             json["title"],
                             json["text"],
                             json["postedDate"],
                             json["numberOfComments"],
                             json["author"],
                             json["picture"].get<std::string>()};
    }

    return std::nullopt;
}

Schedule DatabaseImplDummy::schedule(const std::string &leagueName) const {

    static std::map<std::string, Schedule> fakeData;

    if (fakeData.empty()) {
        using namespace __fakeData;

        const std::vector<Game> games{
            // clang-format off
            Game{randomValue(dates), randomValue(teams), randomValue(teams),randomValue(scores)},
            Game{randomValue(dates), randomValue(teams), randomValue(teams),randomValue(scores)},
            Game{randomValue(dates), randomValue(teams), randomValue(teams),randomValue(scores)},
            Game{randomValue(dates), randomValue(teams), randomValue(teams),randomValue(scores)},
            Game{randomValue(dates), randomValue(teams), randomValue(teams),randomValue(scores)},
        };
        // clang-format on
        Week first{1, games}, second{2, games}, third{3, games};
        Weeks wks{first, second, third};

        Schedule major{wks}, basic{wks}, pretendent{wks};

        fakeData["major"] = major;
        fakeData["basic"] = basic;
        fakeData["pretendent"] = pretendent;
    }

    return fakeData[leagueName];
}

std::optional<GameReport> DatabaseImplDummy::gameReport(id_t id) const {
    using namespace __fakeData;
    std::vector<std::string> scores;

    auto randomStatline = []() -> GameReport::PlayerStatline {
#pragma GCC diagnostic ignored "-Wc++11-narrowing"
        return GameReport::PlayerStatline{
            randomValue(__fakeData::allPlayers),
            std::rand() % 60,
            std::rand() % 50,
            std::rand() % 50,
            std::rand() % 30,
            std::rand() % 30,
            std::rand() % 30,
            std::rand() % 30,
            std::rand() % 30,
            std::rand() % 30,
            std::rand() % 30,
            std::rand() % 10,
            std::rand() % 10,
            std::rand() % 10,
            std::rand() % 5,
            std::rand() % 30,
        };
    };

    std::vector<GameReport::PlayerStatline> hosts, guests;

    std::generate_n(std::back_inserter(hosts), 5 + std::rand() % 7,
                    randomStatline);
    std::generate_n(std::back_inserter(guests), 5 + std::rand() % 7,
                    randomStatline);

    GameReport rep{
        id, randomValue(teams), randomValue(teams), {"", ""}, hosts, guests};
    return rep;
}
std::optional<Standing>
DatabaseImplDummy::standing(const std::string &ln) const {
    Standing fStd{ln};
    return fStd;
}

} // namespace data
} // namespace mlb
