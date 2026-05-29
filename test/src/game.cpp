#include "game.hpp"

#include <gtest/gtest.h>

using namespace chess;

TEST(Game, SetLowSquare)
{
    Bitboard board;
    board |= Square::A8;

    EXPECT_EQ(board.board(), 1uz << 0uz);
}

TEST(Game, SetHighSquare)
{
    Bitboard board;
    board |= Square::H1;

    EXPECT_EQ(board.board(), 1uz << 63uz);
}

TEST(Game, UnsetLowSquare)
{
    Bitboard board;
    board |= Square::A8;
    board |= Square::H1;
    board ^= Square::A8;

    EXPECT_EQ(board.board(), 1uz << 63uz);
}

TEST(Game, UnsetHighSquare)
{
    Bitboard board;
    board |= Square::A8;
    board |= Square::H1;
    board ^= Square::H1;

    EXPECT_EQ(board.board(), 1uz << 0uz);
}
