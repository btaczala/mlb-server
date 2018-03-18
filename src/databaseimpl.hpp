#ifndef DATABASEIMPL_HPP_W6NHBHAO
#define DATABASEIMPL_HPP_W6NHBHAO

#include "database_types.hpp"

namespace mlb {
namespace data {
struct DatabaseImpl {
    Players allPlayers() const { return Players{}; }
    ArticleHeaders articleHeaders() const { return ArticleHeaders{}; }
    std::optional<Article> article(std::uint32_t id) const { return Article{}; }
    Schedule schedule(const std::string &) const { return Schedule{}; }
    std::optional<Schedule> schedule(const std::string &,
                                     std::uint16_t week) const {
        return Schedule{};
    }

    std::optional<GameReport> gameReport(id_t) const { return GameReport{}; }
};
} // namespace data
} // namespace mlb

#endif /* end of include guard: DATABASEIMPL_HPP_W6NHBHAO */
