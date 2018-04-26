#include "databaseimpldummy.hpp"
#include <experimental/filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

#include "log.h"

namespace fs = std::experimental::filesystem;

namespace __fakeData {
const mlb::data::Players allPlayers{{"", "", 10}};

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

} // namespace data
} // namespace mlb
