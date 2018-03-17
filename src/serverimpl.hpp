#ifndef SERVERIMPL_HPP_6MXFQPLZ
#define SERVERIMPL_HPP_6MXFQPLZ

#include <condition_variable>
#include <map>
#include <thread>

#include <cpprest/http_msg.h>

#include "responseconverter.hpp"

namespace mlb {
namespace server {
struct ServerImpl {
    ServerImpl(const web::http::uri& address) : _listener(address) {}
    web::http::experimental::listener::http_listener _listener;

    std::mutex m;
    std::condition_variable cv;
    std::map<web::http::uri, std::function<void(web::http::http_request)>>
        requestsMap;
    data::ResponseConverter converter;
};
}  // namespace server
}  // namespace mlb

#endif /* end of include guard: SERVERIMPL_HPP_6MXFQPLZ */
