#include "server.hpp"
#include "log.h"
#include "restparsers/parsers.hpp"
#include "serverimpl.hpp"
#include "tuple_foreach.hpp"

#include "version.hpp"

#include <chrono>
#include <map>
#include <thread>

namespace {

web::http::uri buildUri(const std::string &address, std::uint16_t port) {
    auto builder = web::http::uri_builder{};
    builder.set_scheme("http").set_host(address).set_port(port).set_path("/");

    mlb_server_trace("Uri = {}", builder.to_string());
    return builder.to_uri();
}

template <typename... Parsers>
void registerParsers(mlb::server::ServerImpl::RequestMap &m,
                     const mlb::data::Database &database) {
    std::tuple<Parsers...> s;
    for_each(s, [&m, &database](const auto &v) {
        using Type = std::decay_t<decltype(v)>;
        m[v.name()] = [&database](web::http::http_request request) {
            Type::parse(request, database);
        };
    });
}
} // namespace

namespace mlb {
namespace server {
Server::Server()
    : d(std::make_unique<ServerImpl>((buildUri("localhost", 9080)))) {
    auto handle_get = [this](web::http::http_request request) {
        mlb_server_trace("HTTP request {}", request.to_string());

        const auto paths =
            web::http::uri::split_path(request.request_uri().to_string());

        if (paths.size() < 2) {
            request.reply(web::http::status_codes::NotAcceptable);
            return;
        }

        mlb_server_debug("Requested info {}", paths.at(1));

        const auto it = d->requestsMap.find(paths.at(1));
        if (it == d->requestsMap.end()) {
            mlb_server_warn("Unable to find uri {}",
                            request.request_uri().to_string());
            request.reply(web::http::status_codes::NotAcceptable);
            return;
        }

        it->second(request);
    };

    registerParsers<restParsers::ArticleParser, restParsers::Schedule,
                    restParsers::Game, restParsers::Player,
                    restParsers::ArticleHeadersParser>(d->requestsMap,
                                                       database);

    d->_listener.support(web::http::methods::GET, handle_get);

    d->requestsMap["version"] = [this](web::http::http_request req) {
        const mlb::server::Version v;
        const auto response = ResponseConverter::serialize(v);
        req.reply(web::http::status_codes::OK, response);
    };

    d->requestsMap["ping"] = [](web::http::http_request req) {
        req.reply(web::http::status_codes::OK);
    };
};

Server::~Server() {}

void Server::start() {
    d->_listener.open()
        .then([this]() {
            mlb_server_info("Starting server on uri {}",
                            d->_listener.uri().to_string());
        })
        .wait();
    std::unique_lock<std::mutex> lk(d->m);
    d->working.store(true);
    while (d->cv.wait_for(lk, std::chrono::seconds(5)) ==
           std::cv_status::timeout) {
        mlb_server_trace("Server is still working");
    }

    mlb_server_info("Server exiting");
}

void Server::stop() {
    mlb_server_info("Stopping server");
    if (!d->working.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    d->cv.notify_one();
}

bool Server::isRunning() const noexcept { return d->working.load(); }

} // namespace server
} // namespace mlb
