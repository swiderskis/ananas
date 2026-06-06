#include "chesslib/square.hpp"

#include <gtest/gtest.h>

using namespace chess;

TEST(Square, RankOne)
{
    EXPECT_TRUE(square::is_in(Square::A1, Rank::One));
    EXPECT_TRUE(square::is_in(Square::B1, Rank::One));
    EXPECT_TRUE(square::is_in(Square::C1, Rank::One));
    EXPECT_TRUE(square::is_in(Square::D1, Rank::One));
    EXPECT_TRUE(square::is_in(Square::E1, Rank::One));
    EXPECT_TRUE(square::is_in(Square::F1, Rank::One));
    EXPECT_TRUE(square::is_in(Square::G1, Rank::One));
    EXPECT_TRUE(square::is_in(Square::H1, Rank::One));
}

TEST(Square, RankEight)
{
    EXPECT_TRUE(square::is_in(Square::A8, Rank::Eight));
    EXPECT_TRUE(square::is_in(Square::B8, Rank::Eight));
    EXPECT_TRUE(square::is_in(Square::C8, Rank::Eight));
    EXPECT_TRUE(square::is_in(Square::D8, Rank::Eight));
    EXPECT_TRUE(square::is_in(Square::E8, Rank::Eight));
    EXPECT_TRUE(square::is_in(Square::F8, Rank::Eight));
    EXPECT_TRUE(square::is_in(Square::G8, Rank::Eight));
    EXPECT_TRUE(square::is_in(Square::H8, Rank::Eight));
}

TEST(Square, FileA)
{
    EXPECT_TRUE(square::is_in(Square::A1, File::A));
    EXPECT_TRUE(square::is_in(Square::A2, File::A));
    EXPECT_TRUE(square::is_in(Square::A3, File::A));
    EXPECT_TRUE(square::is_in(Square::A4, File::A));
    EXPECT_TRUE(square::is_in(Square::A5, File::A));
    EXPECT_TRUE(square::is_in(Square::A6, File::A));
    EXPECT_TRUE(square::is_in(Square::A7, File::A));
    EXPECT_TRUE(square::is_in(Square::A8, File::A));
}

TEST(Square, FileH)
{
    EXPECT_TRUE(square::is_in(Square::H1, File::H));
    EXPECT_TRUE(square::is_in(Square::H2, File::H));
    EXPECT_TRUE(square::is_in(Square::H3, File::H));
    EXPECT_TRUE(square::is_in(Square::H4, File::H));
    EXPECT_TRUE(square::is_in(Square::H5, File::H));
    EXPECT_TRUE(square::is_in(Square::H6, File::H));
    EXPECT_TRUE(square::is_in(Square::H7, File::H));
    EXPECT_TRUE(square::is_in(Square::H8, File::H));
}

TEST(Square, DirNW)
{
    auto const square = Square::E4;
    auto const new_square = square::at(square, Dir::NW);

    EXPECT_EQ(new_square.value(), Square::D5);
}

TEST(Square, DirN)
{
    auto const square = Square::E4;
    auto const new_square = square::at(square, Dir::N);

    EXPECT_EQ(new_square.value(), Square::E5);
}

TEST(Square, DirNE)
{
    auto const square = Square::E4;
    auto const new_square = square::at(square, Dir::NE);

    EXPECT_EQ(new_square.value(), Square::F5);
}

TEST(Square, DirE)
{
    auto const square = Square::E4;
    auto const new_square = square::at(square, Dir::E);

    EXPECT_EQ(new_square.value(), Square::F4);
}

TEST(Square, DirSE)
{
    auto const square = Square::E4;
    auto const new_square = square::at(square, Dir::SE);

    EXPECT_EQ(new_square.value(), Square::F3);
}

TEST(Square, DirS)
{
    auto const square = Square::E4;
    auto const new_square = square::at(square, Dir::S);

    EXPECT_EQ(new_square.value(), Square::E3);
}

TEST(Square, DirSW)
{
    auto const square = Square::E4;
    auto const new_square = square::at(square, Dir::SW);

    EXPECT_EQ(new_square.value(), Square::D3);
}

TEST(Square, DirW)
{
    auto const square = Square::E4;
    auto const new_square = square::at(square, Dir::W);

    EXPECT_EQ(new_square.value(), Square::D4);
}

TEST(Square, DirNWNull)
{
    auto const square = Square::A8;
    auto const new_square = square::at(square, Dir::NW);

    EXPECT_FALSE(new_square.has_value());
}

TEST(Square, DirNNull)
{
    auto const square = Square::A8;
    auto const new_square = square::at(square, Dir::N);

    EXPECT_FALSE(new_square.has_value());
}

TEST(Square, DirNENull)
{
    auto const square = Square::H8;
    auto const new_square = square::at(square, Dir::NE);

    EXPECT_FALSE(new_square.has_value());
}

TEST(Square, DirENull)
{
    auto const square = Square::H1;
    auto const new_square = square::at(square, Dir::E);

    EXPECT_FALSE(new_square.has_value());
}

TEST(Square, DirSENull)
{
    auto const square = Square::H1;
    auto const new_square = square::at(square, Dir::SE);

    EXPECT_FALSE(new_square.has_value());
}

TEST(Square, DirSNull)
{
    auto const square = Square::H1;
    auto const new_square = square::at(square, Dir::S);

    EXPECT_FALSE(new_square.has_value());
}

TEST(Square, DirSWNull)
{
    auto const square = Square::A1;
    auto const new_square = square::at(square, Dir::SW);

    EXPECT_FALSE(new_square.has_value());
}

TEST(Square, DirWNull)
{
    auto const square = Square::A8;
    auto const new_square = square::at(square, Dir::W);

    EXPECT_FALSE(new_square.has_value());
}
