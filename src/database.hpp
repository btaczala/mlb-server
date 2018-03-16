#ifndef DATABASE_HPP_DL31MKFQ
#define DATABASE_HPP_DL31MKFQ

#include <vector>

#include <functional>

#include "database_types.hpp"

namespace mlb {
namespace data {
struct Database {
    Database() = default;

    template <typename DatabaseImpl>
    void setImpl(DatabaseImpl&& db) {
        _getAllPlayers = [&db]() { return db.allPlayers(); };
        _articleHeaders = [&db]() { return db.articleHeaders(); };
    }

    Players allPlayers() const;
    ArticleHeaders articleHeaders() const { return _articleHeaders(); }

   private:
    std::function<std::vector<PlayerShortInfo>()> _getAllPlayers;
    std::function<ArticleHeaders()> _articleHeaders;
};
}  // namespace data
}  // namespace mlb

#endif /* end of include guard: DATABASE_HPP_DL31MKFQ */
