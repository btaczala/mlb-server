#ifndef DATABASE_TYPES_HPP_GBPJYENR
#define DATABASE_TYPES_HPP_GBPJYENR

#include <optional>
#include <string>
#include <vector>

#include <date/date.h>

namespace mlb {
namespace data {

using id_t = std::uint32_t;
using DateTime = std::chrono::time_point<std::chrono::system_clock, date::days>;

struct PlayerShortInfo {
    std::string firstName;
    std::string lastName;
    std::uint32_t id;
};

struct Team {
    std::string name;
    std::uint32_t id;
};

struct Picture {
    std::string url;
};

struct User {
    std::string firstName;
    std::string lastName;
};

struct Comment {
    id_t id;
    User user;
    std::string text;
    DateTime date;
};

struct ArticleHeader {
    id_t id;
    std::string title;
    std::string text;
    std::string postedDate;
    std::uint32_t numberOfComments;
    std::string author;
    Picture picture;
    std::vector<Comment> comments;
};

struct Game {
    std::string datetime;
    Team host;
    Team guest;
    std::string score;
};

struct Week {
    std::uint16_t weekNumber;
    std::vector<Game> games;
};

struct GameReport {
    id_t id;
    Team host;
    Team guest;
    std::vector<std::string> scores;

    struct PlayerStatline {
        PlayerShortInfo id;
        std::uint16_t points;
        // 2 points
        std::uint16_t fgm;
        std::uint16_t fga;
        // 3pts
        std::uint16_t tpm;
        std::uint16_t tpa;
        // free throws
        std::uint16_t ftm;
        std::uint16_t fta;

        std::uint16_t defensiveRebounds;
        std::uint16_t ofensiveRebounds;

        std::uint16_t assists;
        std::uint16_t steals;
        std::uint16_t blocks;
        std::uint16_t turnovers;
        std::uint16_t fouls;
        std::uint16_t eval;
    };

    std::vector<PlayerStatline> hostStats;
    std::vector<PlayerStatline> guestStats;
};

struct Standing {
    std::string leagueName;

    struct StandingEntry {
        Team team;
        std::uint32_t games;
        std::uint32_t wins;
        std::uint32_t losts;
        std::string bilans;
        std::int32_t diff;
        std::uint32_t points;
    };

    std::vector<StandingEntry> teams;
};

using Players = std::vector<PlayerShortInfo>;
using ArticleHeaders = std::vector<ArticleHeader>;
using Weeks = std::vector<Week>;

struct Schedule {
    Weeks weeks;
};

} // namespace data
} // namespace mlb

#endif /* end of include guard: DATABASE_TYPES_HPP_GBPJYENR */
