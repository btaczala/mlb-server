#ifndef DATABASE_MOCK_HPP_KEBRJD9L
#define DATABASE_MOCK_HPP_KEBRJD9L

#include <gmock/gmock.h>

#include "database_types.hpp"

struct DatabaseMock {
    MOCK_CONST_METHOD0(allPlayers, mlb::data::Players());
    MOCK_CONST_METHOD0(articleHeaders, mlb::data::ArticleHeaders());
};

#endif /* end of include guard: DATABASE_MOCK_HPP_KEBRJD9L */
