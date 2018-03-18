#ifndef DATABASE_TYPES_HPP_GBPJYENR
#define DATABASE_TYPES_HPP_GBPJYENR

#include <optional>
#include <string>
#include <vector>

namespace mlb {
namespace data {

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
    // FIXME:
    std::string datetime;
    Team host;
    Team guest;
    std::string score;
};
struct Week {
    std::uint16_t weekNumber;
    std::vector<Game> games;
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
