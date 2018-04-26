#ifndef PARSERS_HPP_5LEVGR3J
#define PARSERS_HPP_5LEVGR3J

#include "database.hpp"
#include "responseconverter.hpp"
#include "typestring.hh"

#include <cpprest/http_msg.h>

namespace mlb {

namespace restParsers {
void parseGameReporstRequest(web::http::http_request request,
                             const mlb::data::Database &db,
                             ResponseConverter &converer);

template <typename Derived, typename String>
struct Parser {
    constexpr const char *name() const noexcept { return String::data(); }
};

struct ArticleParser : public Parser<ArticleParser, typestring_is("article")> {
    static void parse(web::http::http_request request,
                      const mlb::data::Database &db);
};

struct ArticleHeadersParser
    : public Parser<ArticleParser, typestring_is("articleHeaders")> {
    static void parse(web::http::http_request request,
                      const mlb::data::Database &db);
};

struct Schedule : public Parser<Schedule, typestring_is("schedule")> {
    static void parse(web::http::http_request request,
                      const mlb::data::Database &db);
};

struct Game : public Parser<Game, typestring_is("gamereport")> {
    static void parse(web::http::http_request request,
                      const mlb::data::Database &db);
};

struct Player : public Parser<Game, typestring_is("player")> {
    static void parse(web::http::http_request request,
                      const mlb::data::Database &db);
};

} // namespace restParsers
} // namespace mlb

#endif /* end of include guard: PARSERS_HPP_5LEVGR3J */
