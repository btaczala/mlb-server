#ifndef DATABASEIMPLDUMMY_HPP_FFTOPMS0
#define DATABASEIMPLDUMMY_HPP_FFTOPMS0

#include "database_types.hpp"

namespace mlb {

namespace data {

struct DatabaseImplDummy {

    DatabaseImplDummy(const std::string &baseDummyDir);

    Players allPlayers() const;
    ArticleHeaders articleHeaders() const;
    std::optional<Article> article(std::uint32_t id) const { return Article{}; }
    Schedule schedule(const std::string &) const { return Schedule{}; }
    std::optional<Schedule> schedule(const std::string &,
                                     std::uint16_t week) const {
        return Schedule{};
    }

    std::optional<GameReport> gameReport(id_t) const { return GameReport{}; }

  private:
    const std::string _rootDir;
};
} // namespace data
} // namespace mlb

#endif /* end of include guard: DATABASEIMPLDUMMY_HPP_FFTOPMS0 */
