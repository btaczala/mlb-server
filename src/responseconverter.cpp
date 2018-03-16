#include "responseconverter.hpp"
#include <cpprest/json.h>

namespace mlb {
namespace data {

namespace {
web::json::value convert(const PlayerShortInfo& p) {
    web::json::value json;
    json["firstname"] = web::json::value(p.firstname);
    json["lastname"] = web::json::value(p.lastname);
    json["id"] = web::json::value(p.id);

    return json;
}
}  // namespace

std::string ResponseConverter::serialize(const Players& players) {
    using namespace web;
    json::value arr;
    std::size_t index = 0;
    for (const auto& p : players) {
        arr[index++] = convert(p);
    }
    return arr.serialize();
}
}  // namespace data
}  // namespace mlb
