
#include <iostream>

#include <cpprest/http_msg.h>

#include "database.hpp"
#include "responseconverter.hpp"
#include "log.h"

namespace mlb {
namespace restParsers {

void parseScheduleRequest(web::http::http_request request,
                          const mlb::data::Database &db,
                          ResponseConverter &converter) {
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
} // namespace restParsers
} // namespace mlb
