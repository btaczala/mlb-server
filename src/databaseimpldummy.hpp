#ifndef DATABASEIMPLDUMMY_HPP_FFTOPMS0
#define DATABASEIMPLDUMMY_HPP_FFTOPMS0

#include "database_types.hpp"

namespace mlb {

namespace data {

struct DatabaseImplDummy {

    DatabaseImplDummy(const std::string &baseDummyDir);

    Players allPlayers() const;
    ArticleHeaders articleHeaders() const;
    std::optional<ArticleHeader> article(std::uint32_t id) const;
    Schedule schedule(const std::string &) const;
    std::optional<Schedule> schedule(const std::string &,
                                     std::uint16_t week) const {
        return Schedule{};
    }

    std::optional<GameReport> gameReport(id_t) const;
    std::optional<Standing> standing(const std::string& ln) const;

  private:
    const std::string _rootDir;
};
} // namespace data
} // namespace mlb

#endif /* end of include guard: DATABASEIMPLDUMMY_HPP_FFTOPMS0 */
