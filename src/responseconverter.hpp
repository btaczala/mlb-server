#ifndef RESPONSECONVERTER_HPP_I8L9MGF3
#define RESPONSECONVERTER_HPP_I8L9MGF3

#include "database_types.hpp"
#include "reflections.hpp"
#include "traits.hpp"

#include <Meta.h>
#include <cpprest/json.h>
#include <nlohmann/json.hpp>
#include <string>

template <typename Value>
nlohmann::json convert(Value &&v) {
    nlohmann::json json;

    using CleanType = typename std::decay<Value>::type;

    if constexpr (is_container<CleanType>::value) {
        std::size_t index = 0;
        std::transform(std::begin(v), std::end(v), std::back_inserter(json),
                       [](const auto &element) { return convert(element); });
    } else {
        static_assert(meta::isRegistered<CleanType>());
        meta::doForAllMembers<CleanType>([&v, &json](const auto &member) {
            using MemberT = typename std::decay<
                meta::get_member_type<decltype(member)>>::type;
            if constexpr (meta::isRegistered<MemberT>() ||
                          is_container<MemberT>::value) {
                json[member.getName()] = convert(member.get(v));
            } else {
                json[member.getName()] = member.get(v);
            }
        });
    }

    return json;
}

struct ResponseConverter {
    template <typename T>
    static std::string serialize(T &&t) {
        const auto v = convert(t);
        return v.dump();
    }
};

#endif /* end of include guard: RESPONSECONVERTER_HPP_I8L9MGF3 */
