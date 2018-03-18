#ifndef PARSERS_HPP_5LEVGR3J
#define PARSERS_HPP_5LEVGR3J

#include "responseconverter.hpp"

namespace mlb {

namespace restParsers {
void parseArticleRequest(web::http::http_request request,
                         const mlb::data::Database &db,
                         ResponseConverter &converer);
void parseScheduleRequest(web::http::http_request request,
                          const mlb::data::Database &db,
                          ResponseConverter &converer);
void parseGameReporstRequest(web::http::http_request request,
                             const mlb::data::Database &db,
                             ResponseConverter &converer);
} // namespace restParsers
} // namespace mlb

#endif /* end of include guard: PARSERS_HPP_5LEVGR3J */
