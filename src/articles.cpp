#include <iostream>

#include <cpprest/http_msg.h>

#include "database.hpp"
#include "responseconverter.hpp"

namespace mlb {
namespace restParsers {

void parseArticleRequest(web::http::http_request request,
                         const mlb::data::Database& db,
                         mlb::data::ResponseConverter& converter) {
    const auto paths =
        web::http::uri::split_path(request.request_uri().to_string());

    if (paths.size() == 2) {
        const auto resp = converter.serialize(db.articleHeaders());
        request.reply(web::http::status_codes::OK, resp);
        return;
    }

    request.reply(web::http::status_codes::NotAcceptable);
}
}  // namespace restParsers
}  // namespace mlb
