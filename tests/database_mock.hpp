#ifndef DATABASE_MOCK_HPP_KEBRJD9L
#define DATABASE_MOCK_HPP_KEBRJD9L

#include <gmock/gmock.h>

#include "database_types.hpp"

struct DatabaseMock {
    MOCK_CONST_METHOD0(allPlayers, mlb::data::Players());
    MOCK_CONST_METHOD0(articleHeaders, mlb::data::ArticleHeaders());
    MOCK_CONST_METHOD1(article,
                       std::optional<mlb::data::ArticleHeader>(std::uint32_t));
    MOCK_CONST_METHOD1(schedule, mlb::data::Schedule(const std::string &));
    MOCK_CONST_METHOD1(standing, mlb::data::Standing(const std::string &));
    MOCK_CONST_METHOD2(schedule,
                       std::optional<mlb::data::Schedule>(const std::string &,
                                                          std::uint16_t));
    MOCK_CONST_METHOD1(gameReport, std::optional<mlb::data::GameReport>(id_t));
};

#endif /* end of include guard: DATABASE_MOCK_HPP_KEBRJD9L */
