#ifndef REFLECTION_HPP_3N0JQKEA
#define REFLECTION_HPP_3N0JQKEA

#include <Meta.h>

#include "database_types.hpp"
#include "version.hpp"

namespace meta {
template <>
inline auto registerMembers<mlb::data::PlayerShortInfo>() {
    return members(member("firstName", &mlb::data::PlayerShortInfo::firstName),
                   member("lastName", &mlb::data::PlayerShortInfo::lastName),
                   member("id", &mlb::data::PlayerShortInfo::id));
}

template <>
inline auto registerMembers<mlb::data::Picture>() {
    return members(member("url", &mlb::data::Picture::url));
}

template <>
inline auto registerMembers<mlb::data::ArticleHeader>() {
    return members(
        member("id", &mlb::data::ArticleHeader::id),
        member("title", &mlb::data::ArticleHeader::title),
        member("postedDate", &mlb::data::ArticleHeader::postedDate),
        member("text", &mlb::data::ArticleHeader::text),
        member("numberOfComments", &mlb::data::ArticleHeader::numberOfComments),
        member("author", &mlb::data::ArticleHeader::author),
        member("picture", &mlb::data::ArticleHeader::picture));
}

template <>
inline auto registerMembers<mlb::data::User>() {
    return members(member("firstName", &mlb::data::User::firstName),
                   member("lastName", &mlb::data::User::lastName));
}

template <>
inline auto registerMembers<mlb::data::Comment>() {
    return members(member("id", &mlb::data::Comment::id),
                   member("user", &mlb::data::Comment::user),
                   member("text", &mlb::data::Comment::text));
}

template <>
inline auto registerMembers<mlb::data::Team>() {
    return members(member("name", &mlb::data::Team::name),
                   member("id", &mlb::data::Team::id));
}

template <>
inline auto registerMembers<mlb::data::Game>() {
    return members(member("id", &mlb::data::Game::id),
                   member("datetime", &mlb::data::Game::datetime),
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
        member("player", &mlb::data::GameReport::PlayerStatline::player),
        member("points", &mlb::data::GameReport::PlayerStatline::points),
        member("fgm", &mlb::data::GameReport::PlayerStatline::fga),
        member("fga", &mlb::data::GameReport::PlayerStatline::fga),
        member("tpm", &mlb::data::GameReport::PlayerStatline::tpm),
        member("tpa", &mlb::data::GameReport::PlayerStatline::tpa),
        member("ftm", &mlb::data::GameReport::PlayerStatline::ftm),
        member("fta", &mlb::data::GameReport::PlayerStatline::fta),
        member("offensiveRebounds",
               &mlb::data::GameReport::PlayerStatline::ofensiveRebounds),
        member("defensiveRebounds",
               &mlb::data::GameReport::PlayerStatline::defensiveRebounds),
        member("assists", &mlb::data::GameReport::PlayerStatline::assists),
        member("steals", &mlb::data::GameReport::PlayerStatline::steals),
        member("blocks", &mlb::data::GameReport::PlayerStatline::blocks),
        member("turnovers", &mlb::data::GameReport::PlayerStatline::turnovers),
        member("fouls", &mlb::data::GameReport::PlayerStatline::fouls),
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
template <>
inline auto registerMembers<mlb::server::Version>() {
    return members(member("major", &mlb::server::Version::major),
                   member("minor", &mlb::server::Version::major),
                   member("release", &mlb::server::Version::major));
}
} // namespace meta

#endif /* end of include guard: REFLECTION_HPP_3N0JQKEA */
