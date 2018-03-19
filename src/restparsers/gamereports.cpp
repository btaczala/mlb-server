#include <cpprest/http_msg.h>

#include "database.hpp"
#include "log.h"
#include "responseconverter.hpp"

namespace mlb {
namespace restParsers {

void parseGameReporstRequest(web::http::http_request request,
                             const mlb::data::Database &db,
                             ResponseConverter &converter) {
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
} // namespace restParsers
} // namespace mlb
