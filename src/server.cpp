#include "server.hpp"
#include "log.h"

#include <chrono>
#include <map>
#include <thread>

namespace {

web::http::uri buildUri(const std::string& address, std::uint16_t port) {
    auto builder = web::http::uri_builder{};
    builder.set_scheme("http").set_host(address).set_port(port).set_path("/");

    mlb_server_trace("Uri = {}", builder.to_string());
    return builder.to_uri();
}
}  // namespace

namespace mlb {
namespace server {
struct ServerImpl {
    ServerImpl(const web::http::uri& address) : _listener(address) {}
    web::http::experimental::listener::http_listener _listener;

    std::mutex m;
    std::condition_variable cv;
    std::map<web::http::uri,
             std::function<web::http::status_code(web::http::http_request)>>
        requestsMap;
};

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
        }

        const auto retCode = it->second(request);
        request.reply(retCode);
    };

    d->_listener.support(web::http::methods::GET, handle_get);

    d->requestsMap["player"] = [this](web::http::http_request) {
        mlb_server_debug("Get player info");

        auto resp = database.allPlayers();
        return web::http::status_codes::OK;
    };
    d->requestsMap["ping"] = [](web::http::http_request) {
        return web::http::status_codes::OK;
    };
}

Server::~Server() {}

void Server::start() {
    d->_listener.open()
        .then([this]() {
            mlb_server_info("Starting server on uri {}",
                            d->_listener.uri().to_string());
        })
        .wait();
    std::unique_lock<std::mutex> lk(d->m);
    while (d->cv.wait_for(lk, std::chrono::seconds(5)) ==
           std::cv_status::timeout) {
        mlb_server_debug("Server working");
    }

    mlb_server_info("Server exiting");
}

void Server::stop() {
    mlb_server_info("Stopping server");
    d->cv.notify_one();
}

}  // namespace server
}  // namespace mlb
