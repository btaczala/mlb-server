#ifndef DATABASEIMPL_HPP_W6NHBHAO
#define DATABASEIMPL_HPP_W6NHBHAO

#include "database_types.hpp"

namespace mlb {
namespace data {
struct DatabaseImpl
{
    Players allPlayers() const { return Players{}; }
    ArticleHeaders articleHeaders() const { return ArticleHeaders {}; }
};
}  // namespace data
}  // namespace mlb

#endif /* end of include guard: DATABASEIMPL_HPP_W6NHBHAO */
