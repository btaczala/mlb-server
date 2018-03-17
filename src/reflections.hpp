#ifndef REFLECTION_HPP_3N0JQKEA
#define REFLECTION_HPP_3N0JQKEA

#include <Meta.h>
#include "database_types.hpp"

namespace meta {
template <>
inline auto registerMembers<mlb::data::PlayerShortInfo>() {
    // clang-format off
    return 
        members(
                member("firstname", &PlayerShortInfo::firstname),
                member("lastname", &PlayerShortInfo::lastname),
                member("id", &PlayerShortInfo::id),
            );
    // clang-format on
}
template <>
inline auto registerMembers<mlb::data::ArticleHeader>() {
    // clang-format off
    return 
        members(
                member("title", &ArticleHeader::title),
                member("postedDate", &ArticleHeader::postedDate), 
                member("numberOfComments", &ArticleHeader::numberOfComments),
                member("author", &ArticleHeader::author),
            );
    // clang-format on
}
}  // namespace meta

#endif /* end of include guard: REFLECTION_HPP_3N0JQKEA */
