#ifndef DATABASE_TYPES_HPP_GBPJYENR
#define DATABASE_TYPES_HPP_GBPJYENR

#include <string>
#include <vector>

namespace mlb {
namespace data {

struct Player {
    std::string firstname;
    std::string lastname;
    std::string id;
};
using Players = std::vector<Player>;
}  // namespace data
}  // namespace mlb

#endif /* end of include guard: DATABASE_TYPES_HPP_GBPJYENR */
