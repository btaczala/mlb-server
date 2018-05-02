#include <gtest/gtest.h>

#include "databaseimpldummy.hpp"
#include "log.h"

struct DatabaseImplDummyTests : public ::testing::Test {

    DatabaseImplDummyTests() : _dummy(DUMMYDATA) {}
    mlb::data::DatabaseImplDummy _dummy;
};

TEST_F(DatabaseImplDummyTests, articles) {
    ASSERT_EQ(_dummy.articleHeaders().size(), 3);
    EXPECT_EQ(_dummy.articleHeaders().at(0).id, 15379383);
}

TEST_F(DatabaseImplDummyTests, schedule) {
    EXPECT_NO_THROW(_dummy.schedule("major"));
    EXPECT_NO_THROW(_dummy.schedule("basic"));
    EXPECT_NO_THROW(_dummy.schedule("pretendent"));
}

int main(int argc, char *argv[]) {
    setupLogger();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
