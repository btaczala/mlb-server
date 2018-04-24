#include <gtest/gtest.h>

#include "databaseimpldummy.hpp"
#include "log.h"

struct DatabaseImplDummyTests : public ::testing::Test {

    DatabaseImplDummyTests() : _dummy(DUMMYDATA) {}
    mlb::data::DatabaseImplDummy _dummy;
};

TEST_F(DatabaseImplDummyTests, articles) {
    ASSERT_EQ(_dummy.articleHeaders().size(), 1);
    EXPECT_EQ(_dummy.articleHeaders().at(0).id, 15379380);
}

int main(int argc, char *argv[]) {
    setupLogger();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
