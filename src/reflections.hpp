#ifndef REFLECTION_HPP_3N0JQKEA
#define REFLECTION_HPP_3N0JQKEA

#include <Meta.h>

#include "database_types.hpp"

namespace meta {
template <>
inline auto registerMembers<mlb::data::PlayerShortInfo>() {
    return members(member("firstname", &mlb::data::PlayerShortInfo::firstname),
                   member("lastname", &mlb::data::PlayerShortInfo::lastname),
                   member("id", &mlb::data::PlayerShortInfo::id));
}

template <>
inline auto registerMembers<mlb::data::ArticleHeader>() {
    return members(
        member("title", &mlb::data::ArticleHeader::title),
        member("postedDate", &mlb::data::ArticleHeader::postedDate),
        member("numberOfComments", &mlb::data::ArticleHeader::numberOfComments),
        member("author", &mlb::data::ArticleHeader::author));
}

template <>
inline auto registerMembers<mlb::data::Team>() {
    return members(member("name", &mlb::data::Team::name),
                   member("id", &mlb::data::Team::id));
}

template <>
inline auto registerMembers<mlb::data::Game>() {
    return members(member("datetime", &mlb::data::Game::datetime),
                   member("host", &mlb::data::Game::host),
                   member("guest", &mlb::data::Game::guest),
                   member("score", &mlb::data::Game::score));
}

template <>
inline auto registerMembers<mlb::data::Week>() {
    return members(member("weeknumber", &mlb::data::Week::weekNumber),
                   member("games", &mlb::data::Week::games));
}

template <>
inline auto registerMembers<mlb::data::Schedule>() {
    return members(member("weeks", &mlb::data::Schedule::weeks));
}

template <>
inline auto registerMembers<mlb::data::GameReport::PlayerStatline>() {
    return members(
        member("id", &mlb::data::GameReport::PlayerStatline::id),
        member("points", &mlb::data::GameReport::PlayerStatline::points),
        member("fgm", &mlb::data::GameReport::PlayerStatline::fga),
        member("fga", &mlb::data::GameReport::PlayerStatline::fga),
        member("tpm", &mlb::data::GameReport::PlayerStatline::tpm),
        member("tpa", &mlb::data::GameReport::PlayerStatline::tpa),
        member("ftm", &mlb::data::GameReport::PlayerStatline::ftm),
        member("fta", &mlb::data::GameReport::PlayerStatline::fta),
        member("eval", &mlb::data::GameReport::PlayerStatline::eval));
}

template <>
inline auto registerMembers<mlb::data::GameReport>() {
    return members(member("id", &mlb::data::GameReport::id),
                   member("host", &mlb::data::GameReport::host),
                   member("guest", &mlb::data::GameReport::guest),
                   member("scores", &mlb::data::GameReport::scores),
                   member("hostStats", &mlb::data::GameReport::hostStats),
                   member("guestStats", &mlb::data::GameReport::guestStats));
}
} // namespace meta

#endif /* end of include guard: REFLECTION_HPP_3N0JQKEA */
