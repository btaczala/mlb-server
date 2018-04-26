#ifndef DATABASE_HPP_DL31MKFQ
#define DATABASE_HPP_DL31MKFQ

#include <functional>
#include <optional>
#include <vector>

#include "database_types.hpp"

namespace mlb {
namespace data {
struct Database {
    Database() = default;

    template <typename DatabaseImpl>
    void setImpl(DatabaseImpl &&db) {
        _getAllPlayers = [&db]() { return db.allPlayers(); };
        _articleHeaders = [&db]() { return db.articleHeaders(); };
        _article = [&db](std::uint32_t id) { return db.article(id); };
        _schedule = [&db](const std::string &league) {
            return db.schedule(league);
        };
        _scheduleByWeek = [&db](const std::string &league, std::uint16_t week) {
            return db.schedule(league, week);
        };

        _gameReport = [&db](id_t id) { return db.gameReport(id); };
    }

    Players allPlayers() const { return _getAllPlayers(); }
    ArticleHeaders articleHeaders() const { return _articleHeaders(); }

    std::optional<ArticleHeader> article(std::uint32_t id) const {
        return _article(id);
    }

    Schedule schedule(const std::string &league) const {
        return _schedule(league);
    }

    std::optional<Schedule> schedule(const std::string &league,
                                     std::uint16_t week) const {
        return _scheduleByWeek(league, week);
    }

    std::optional<GameReport> gameReport(id_t id) const {
        return _gameReport(id);
    }

  private:
    std::function<Players()> _getAllPlayers;
    std::function<ArticleHeaders()> _articleHeaders;
    std::function<std::optional<ArticleHeader>(std::uint32_t)> _article;
    std::function<Schedule(const std::string &)> _schedule;
    std::function<std::optional<Schedule>(const std::string &, std::uint16_t)>
        _scheduleByWeek;
    std::function<std::optional<GameReport>(id_t)> _gameReport;
};
} // namespace data
} // namespace mlb

#endif /* end of include guard: DATABASE_HPP_DL31MKFQ */
