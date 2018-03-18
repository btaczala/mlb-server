#ifndef DATABASE_TYPES_HPP_GBPJYENR
#define DATABASE_TYPES_HPP_GBPJYENR

#include <optional>
#include <string>
#include <vector>

namespace mlb {
namespace data {

using id_t = std::uint32_t;

struct PlayerShortInfo {
    std::string firstname;
    std::string lastname;
    std::uint32_t id;
};

struct Team {
    std::string name;
    std::uint32_t id;
};

struct ArticleHeader {
    std::string title;
    std::string postedDate;
    std::uint32_t numberOfComments;
    std::string author;
};

struct Comment {};

struct Article {
    std::string title;
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

using Players = std::vector<PlayerShortInfo>;
using ArticleHeaders = std::vector<ArticleHeader>;
using Weeks = std::vector<Week>;

struct Schedule {
    Weeks weeks;
};

} // namespace data
} // namespace mlb

#endif /* end of include guard: DATABASE_TYPES_HPP_GBPJYENR */
