#include "chesslib/game.hpp"

#include "chesslib/piece.hpp"
#include "chesslib/square.hpp"

#include <gtest/gtest.h>

using namespace chess;

TEST(Bitboard, SetLowSquare)
{
    auto const square = Square::A8;
    Bitboard board;
    board |= square;

    EXPECT_EQ(board.board(), 1uz << 0uz);
    EXPECT_TRUE(board.is_set(square));
}

TEST(Bitboard, SetHighSquare)
{
    auto const square = Square::H1;
    Bitboard board;
    board |= square;

    EXPECT_EQ(board.board(), 1uz << 63uz);
    EXPECT_TRUE(board.is_set(square));
}

TEST(Bitboard, UnsetLowSquare)
{
    auto const square1 = Square::A8;
    auto const square2 = Square::H1;
    Bitboard board;
    board |= square1;
    board |= square2;
    board ^= square1;

    EXPECT_EQ(board.board(), 1uz << 63uz);
    EXPECT_TRUE(board.is_set(square2));
    EXPECT_FALSE(board.is_set(square1));
}

TEST(Bitboard, UnsetHighSquare)
{
    auto const square1 = Square::A8;
    auto const square2 = Square::H1;
    Bitboard board;
    board |= square1;
    board |= square2;
    board ^= square2;

    EXPECT_EQ(board.board(), 1uz << 0uz);
    EXPECT_TRUE(board.is_set(square1));
    EXPECT_FALSE(board.is_set(square2));
}

TEST(Game, PieceAtWhite)
{
    auto const piece = Piece::Pawn;
    auto const side = Side::White;
    auto const square = Square::E4;
    auto const game = [=]() {
        GameBuilder game_builder;
        game_builder.set_square(piece, side, square);
        return game_builder.build();
    }();

    EXPECT_EQ(game.board(piece, side).board(), 1uz << 36uz);
    EXPECT_TRUE(game.board(piece, side).is_set(square));
}

TEST(Game, PieceAtBlack)
{
    auto const piece = Piece::King;
    auto const side = Side::Black;
    auto const square = Square::D5;
    auto const game = [=]() {
        GameBuilder game_builder;
        game_builder.set_square(piece, side, square);
        return game_builder.build();
    }();

    EXPECT_EQ(game.board(piece, side).board(), 1uz << 27uz);
    EXPECT_TRUE(game.board(piece, side).is_set(square));
}
