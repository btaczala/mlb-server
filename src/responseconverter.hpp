#ifndef RESPONSECONVERTER_HPP_I8L9MGF3
#define RESPONSECONVERTER_HPP_I8L9MGF3

#include "database_types.hpp"
#include "reflections.hpp"
#include "traits.hpp"

#include <Meta.h>
#include <cpprest/json.h>
#include <nlohmann/json.hpp>
#include <string>

template <typename T, typename JsonType = nlohmann::json>
struct is_convertible {
    constexpr static bool value =
        meta::isRegistered<T>() ||
        nlohmann::detail::has_from_json<JsonType, T>::value;
};

template <typename T>
struct is_supported_container {
    constexpr static bool value = is_vector<T>::value;
};

template <typename Value>
nlohmann::json convert(Value &&v) {
    nlohmann::json json;

    using CleanType = typename std::decay<Value>::type;
    static_assert(
        is_convertible<CleanType>::value,
        "Type must be registered to metastuff or convertible to json");

    // For containers :
    // iterate over the container and pass each element to convert function
    if constexpr (is_supported_container<CleanType>::value) {
        std::size_t index = 0;
        std::transform(std::begin(v), std::end(v), std::back_inserter(json),
                       [](const auto &element) { return convert(element); });

        return json;
        // For registered types to metaStuff
    } else if constexpr (meta::isRegistered<CleanType>()) {
        meta::doForAllMembers<CleanType>([&v, &json](const auto &member) {
            using MemberT = typename std::decay<
                meta::get_member_type<decltype(member)>>::type;
            if constexpr (meta::isRegistered<MemberT>() ||
                          is_supported_container<MemberT>::value) {
                json[member.getName()] = convert(member.get(v));
            } else {
                json[member.getName()] = member.get(v);
            }
        });
        // For all other types like built-in ones
    } else {
        json = std::forward<Value>(v);
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
