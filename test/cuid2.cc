#include <gtest/gtest.h>

#include <cctype>

#include <cuid2/cuid2.h>
#include <cuid2/constant.h>


TEST(CUID, AssertDefaultLength) {
    EXPECT_EQ(cuid2::createId().length(),                           cuid2::DEFAULT_LENGTH);
}

TEST(CUID, AssertBigLength) {
    EXPECT_EQ(cuid2::createId(cuid2::BIG_LENGTH).length(),          cuid2::BIG_LENGTH);
}

TEST(CUID, AssertMinLength) {
    EXPECT_EQ(cuid2::createId(cuid2::MIN_LENGTH - 2).length(),      cuid2::MIN_LENGTH);
}

TEST(CUID, AssertAlphaLetter) {
    auto id = cuid2::createId();
    EXPECT_TRUE(isalpha(id[0]));
}

TEST(CUID, AssertUnique) {
    EXPECT_FALSE(cuid2::createId() == cuid2::createId());
    EXPECT_FALSE(cuid2::createId() == cuid2::createId());
    EXPECT_FALSE(cuid2::createId() == cuid2::createId());
    EXPECT_FALSE(cuid2::createId() == cuid2::createId());
    EXPECT_FALSE(cuid2::createId() == cuid2::createId());
}