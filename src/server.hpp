#ifndef SERVER_HPP_CGSWFYJI
#define SERVER_HPP_CGSWFYJI

#include <cpprest/http_listener.h>
#include <memory>

#include "database.hpp"

namespace mlb {
namespace server {

struct ServerImpl;

struct Server {
    Server();
    ~Server();

    void start();
    void stop();

    template <typename DatabaseImpl>
    void setDatabaseImpl(DatabaseImpl&& db) {
        database.setImpl(std::forward<DatabaseImpl>(db));
    }

   private:
    std::unique_ptr<ServerImpl> d;
    data::Database database;
};
}  // namespace server
}  // namespace mlb

#endif /* end of include guard: SERVER_HPP_CGSWFYJI */
