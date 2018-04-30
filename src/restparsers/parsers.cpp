#include "parsers.hpp"
#include "database.hpp"
#include "log.h"
#include "responseconverter.hpp"

#include <cpprest/http_msg.h>

namespace mlb {
namespace restParsers {
using namespace web::http;

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
        const auto json = ResponseConverter::serialize(art.value());

        mlb_server_debug("Sending json = {}", json);
        request.reply(status_codes::OK, json);
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

    mlb_server_debug("Sending response {}", tmpArts.size());
    const auto resp = ResponseConverter::serialize(tmpArts);
    mlb_server_debug("Response is {}", resp);
    request.reply(status_codes::OK, resp);
}

void Schedule::parse(web::http::http_request request,
                     const mlb::data::Database &db) {
    using namespace web::http;
    const auto paths =
        web::http::uri::split_path(request.request_uri().to_string());

    mlb_server_debug("Uri = {}", request.request_uri().to_string());
    if (paths.size() < 3) {
        request.reply(status_codes::MethodNotAllowed);
        return;
    }

    if (paths.size() == 3) {
        auto sched = db.schedule(paths.at(2));
        request.reply(status_codes::OK);
        return;
    } else if (paths.size() == 4) {
        const auto weekID = std::stoi(paths.at(3));
        auto sched = db.schedule(paths.at(2), weekID);

        if (sched) {
            request.reply(status_codes::OK,
                          ResponseConverter::serialize(sched.value()));
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
        request.reply(web::http::status_codes::OK,
                      ResponseConverter::serialize(report.value()));
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
} // namespace restParsers
} // namespace mlb
