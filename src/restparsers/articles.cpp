#include <iostream>

#include <cpprest/http_msg.h>

#include "database.hpp"
#include "responseconverter.hpp"

namespace mlb {
namespace restParsers {

void parseArticleRequest(web::http::http_request request,
                         const mlb::data::Database &db,
                         ResponseConverter &converter) {
    const auto paths =
        web::http::uri::split_path(request.request_uri().to_string());

    using namespace web::http;
    if (paths.size() == 2) {
        const auto resp = converter.serialize(db.articleHeaders());
        request.reply(status_codes::OK, resp);
        return;
    } else if (paths.size() == 3) {
        const auto artId = std::stoi(paths.at(2));
        const auto art = db.article(artId);

        if (art) {
            request.reply(status_codes::OK);
        } else {
            request.reply(status_codes::NotFound);
        }
    }

    request.reply(web::http::status_codes::NotAcceptable);
}
} // namespace restParsers
} // namespace mlb
