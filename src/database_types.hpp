#ifndef DATABASE_TYPES_HPP_GBPJYENR
#define DATABASE_TYPES_HPP_GBPJYENR

#include <string>
#include <vector>

namespace mlb {
namespace data {

struct PlayerShortInfo {
    std::string firstname;
    std::string lastname;
    std::string id;
};

struct ArticleHeader {
    std::string title;
    std::string postedDate;
    std::uint32_t numberOfComments;
    std::string author;
};

using Players = std::vector<PlayerShortInfo>;
using ArticleHeaders = std::vector<ArticleHeader>;
}  // namespace data
}  // namespace mlb

#endif /* end of include guard: DATABASE_TYPES_HPP_GBPJYENR */
