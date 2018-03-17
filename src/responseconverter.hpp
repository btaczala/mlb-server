#ifndef RESPONSECONVERTER_HPP_I8L9MGF3
#define RESPONSECONVERTER_HPP_I8L9MGF3

#include <Meta.h>
#include <cpprest/json.h>
#include <string>
#include "database_types.hpp"
#include "traits.hpp"

namespace mlb {
namespace data {

template <typename Val>
web::json::value convert(Val&& v) {
    web::json::value json;

    meta::doForAllMembers<Val>([&v, &json](const auto& member) {
        json[member.getName()] = member.get(v);
    });

    return json;
}

struct ResponseConverter {
    template <typename Container,
              typename = std::enable_if_t<is_container<Container>::value>>
    std::string serialize(Container&& c) {
        using namespace web;
        json::value arr;
        std::size_t index = 0;
        std::for_each(std::begin(c), std::end(c),
                      [&arr, &index](const auto& element) {
                          arr[index++] = convert(element);
                      });
        return arr.serialize();
    }
};
}  // namespace data
}  // namespace mlb

#endif /* end of include guard: RESPONSECONVERTER_HPP_I8L9MGF3 */
