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
        _getAllPlayers = [&db]() { return db.getAllPlayers(); };
    }

    Players allPlayers() const;

   private:
    std::function<std::vector<Player>()> _getAllPlayers;
};
}  // namespace data
}  // namespace mlb

#endif /* end of include guard: DATABASE_HPP_DL31MKFQ */
