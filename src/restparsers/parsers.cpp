#include "parsers.hpp"
#include "database.hpp"
#include "log.h"
#include "responseconverter.hpp"

#include <cpprest/http_msg.h>
#include <experimental/filesystem>

extern bool bDumpJson;

template <typename T>
struct is_optional {
    constexpr static const bool value = false;
};

template <typename T>
struct is_optional<std::optional<T>> {
    constexpr static const bool value = true;
};

namespace {
std::string random_string(size_t length) {
    auto randchar = []() -> char {
        const char charset[] = "0123456789"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}
std::string storeJson(const std::string &jsonData) {
    namespace fs = std::experimental::filesystem;

    const fs::path jsonDirPath = fs::temp_directory_path() / fs::path{"jsons"};

    if (!fs::exists(jsonDirPath)) {
        fs::create_directories(jsonDirPath);
    }

    const fs::path tmpDirPath =
        jsonDirPath / fs::path{random_string(10) + ".json"};

    std::ofstream file{tmpDirPath.c_str()};
    file << jsonData;

    return tmpDirPath.string();
}
} // namespace

namespace mlb {
namespace restParsers {

using namespace web::http;

template <typename T>
void ok(web::http::http_request &request, T &&t) {

    using RealType = std::decay_t<T>;
    std::string json;
    if constexpr (is_optional<RealType>::value) {
        json = ResponseConverter::serialize(t.value());
    } else {
        json = ResponseConverter::serialize(std::forward<T>(t));
    }

    if (bDumpJson) {
        mlb_server_debug("OK, sending response , json saved under {}",
                         storeJson(json));
    }
    request.reply(status_codes::OK, json);
}

void ArticleParser::parse(web::http::http_request request,
                          const mlb::data::Database &db) {
    const auto paths = uri::split_path(request.request_uri().to_string());

    if (paths.size() != 3) {
        request.reply(web::http::status_codes::NotAcceptable);
    }

    const auto artId = std::stoi(paths.at(2));
    const auto art = db.article(artId);
    mlb_server_debug("Requesting article {}", artId);

    if (art) {
        ok(request, art);
    } else {
        request.reply(status_codes::NotFound);
    }
}

void ArticleHeadersParser::parse(web::http::http_request request,
                                 const mlb::data::Database &db) {
    const auto paths = uri::split_path(request.request_uri().to_string());

    mlb_server_debug("ArticleHeaders::parse()");
    data::ArticleHeaders tmpArts = db.articleHeaders();
    if (paths.size() == 2) {
        // default implementation get last 10 articles
        if (tmpArts.size() > 10) {
            tmpArts.resize(10);
        }
    } else if (paths.size() == 3) {
        const auto numberOfArticles = std::stoi(paths.at(2));
        if (tmpArts.size() > numberOfArticles) {
            tmpArts.resize(numberOfArticles);
        }
    }

    ok(request, tmpArts);
}

void Schedule::parse(web::http::http_request request,
                     const mlb::data::Database &db) {
    using namespace web::http;
    const auto paths =
        web::http::uri::split_path(request.request_uri().to_string());

    mlb_server_debug("Uri = {}", request.request_uri().to_string());
    if (paths.size() < 2) {
        request.reply(status_codes::MethodNotAllowed);
        return;
    }

    if (paths.size() == 2) {
        // get schedule for all
        auto majorSched = db.schedule("major");
        auto pretendentSched = db.schedule("pretendent");
        auto basicSched = db.schedule("basic");

        const std::map<std::string, mlb::data::Schedule> schedules{
            std::make_pair("major", majorSched),
            std::make_pair("pretendent", pretendentSched),
            std::make_pair("basic", basicSched)};

        ok(request, schedules);
    }

    if (paths.size() == 3) {
        ok(request, db.schedule(paths.at(2)));
        return;
    } else if (paths.size() == 4) {
        const auto weekID = std::stoi(paths.at(3));
        auto sched = db.schedule(paths.at(2), weekID);

        if (sched) {
            ok(request, sched.value());
            return;
        } else {
            request.reply(status_codes::NotFound);
            return;
        }
    }
}

void Standings::parse(web::http::http_request request,
                      const mlb::data::Database &db) {
    using namespace web::http;
    const auto paths =
        web::http::uri::split_path(request.request_uri().to_string());

    mlb_server_debug("Uri = {}", request.request_uri().to_string());

    if (paths.size() != 2 && paths.size() != 3) {
        request.reply(status_codes::MethodNotAllowed);
        return;
    }

    if (paths.size() == 2) {
        // get all
        //
    }
}

void Game::parse(web::http::http_request request,
                 const mlb::data::Database &db) {
    const auto paths =
        web::http::uri::split_path(request.request_uri().to_string());

    if (paths.size() != 3) {
        request.reply(web::http::status_codes::NotAcceptable);
        return;
    }

    auto id = std::stoi(paths.at(2));

    auto report = db.gameReport(id);

    if (report) {
        ok(request, report.value());
    } else {
        request.reply(web::http::status_codes::NotFound);
    }
}

void Player::parse(web::http::http_request request,
                   const mlb::data::Database &db) {
    mlb_server_debug("Get player info");
    const auto response = ResponseConverter::serialize(db.allPlayers());
    mlb_server_info("Sending response {}", response);
    request.reply(web::http::status_codes::OK, response);
}

void Gallery::parse(web::http::http_request request,
                    const mlb::data::Database &db) {
    mlb_server_debug("Get gallery info");
    const auto paths = uri::split_path(request.request_uri().to_string());

    if (paths.size() == 2) {
        ok(request, db.galleryList());
    } else if (paths.size() == 3) {

        const auto gallery = db.gallery(std::stoi(paths.at(2)));

        if (gallery)
            ok(request, gallery.value());
        else
            request.reply(web::http::status_codes::NotFound);
    }
}
} // namespace restParsers
} // namespace mlb
