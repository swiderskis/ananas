#include "chess.hpp"

#include <gtest/gtest.h>

TEST(Chess, HelloWorld)
{
    EXPECT_EQ(chess::hello_world(), "Hello world!");
}
