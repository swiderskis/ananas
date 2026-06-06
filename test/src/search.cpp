#include "chesslib/search.hpp"

#include "chesslib/game.hpp"
#include "chesslib/piece.hpp"
#include "chesslib/square.hpp"

#include <algorithm>
#include <gtest/gtest.h>

using namespace chess;

TEST(Search, PawnSinglePushWhite)
{
    auto const piece = Piece::Pawn;
    auto const side = Side::White;
    auto const source = Square::E3;
    auto const target = Square::E4;
    auto const game = [=]() {
        GameBuilder game_builder;
        game_builder.set_square(piece, side, source);
        return game_builder.build();
    }();
    auto const moves = search::find_moves(game);
    Move const expected_move{ source, target, piece };

    EXPECT_TRUE(std::ranges::contains(moves, expected_move));
    EXPECT_EQ(moves.size(), 1);
}

TEST(Search, PawnSinglePushBlack)
{
    auto const piece = Piece::Pawn;
    auto const side = Side::Black;
    auto const source = Square::D6;
    auto const target = Square::D5;
    auto const game = [=]() {
        GameBuilder game_builder;
        game_builder.set_square(piece, side, source);
        game_builder.set_to_move(side);
        return game_builder.build();
    }();
    auto const moves = search::find_moves(game);
    Move const expected_move{ source, target, piece };

    EXPECT_TRUE(std::ranges::contains(moves, expected_move));
    EXPECT_EQ(moves.size(), 1);
}

TEST(Search, PawnDoublePushWhite)
{
    auto const piece = Piece::Pawn;
    auto const side = Side::White;
    auto const source = Square::E2;
    auto const target = Square::E4;
    auto const game = [=]() {
        GameBuilder game_builder;
        game_builder.set_square(piece, side, source);
        return game_builder.build();
    }();
    auto const moves = search::find_moves(game);
    Move const expected_move{ source, target, piece };

    EXPECT_TRUE(std::ranges::contains(moves, expected_move));
    EXPECT_EQ(moves.size(), 2);
}

TEST(Search, PawnDoublePushBlack)
{
    auto const piece = Piece::Pawn;
    auto const side = Side::Black;
    auto const source = Square::D7;
    auto const target = Square::D5;
    auto const game = [=]() {
        GameBuilder game_builder;
        game_builder.set_square(piece, side, source);
        game_builder.set_to_move(side);
        return game_builder.build();
    }();
    auto const moves = search::find_moves(game);
    Move const expected_move{ source, target, piece };

    EXPECT_TRUE(std::ranges::contains(moves, expected_move));
    EXPECT_EQ(moves.size(), 2);
}

TEST(Search, PawnCaptureWhite)
{
    auto const piece = Piece::Pawn;
    auto const side = Side::White;
    auto const opponent_side = Side::Black;
    auto const source = Square::E4;
    std::array const targets{ Square::D5, Square::F5 };
    std::array const non_targets{ Square::D3, Square::F3 };
    auto const game = [=] {
        GameBuilder game_builder;
        game_builder.set_square(piece, side, source);
        auto const set_square = [&game_builder](auto t) { game_builder.set_square(piece, opponent_side, t); };
        std::ranges::for_each(targets, set_square);
        std::ranges::for_each(non_targets, set_square);
        return game_builder.build();
    }();
    auto const moves = search::find_moves(game);
    Move const expected_move1{ source, targets[0], piece };
    Move const expected_move2{ source, targets[1], piece };
    Move const unexpected_move1{ source, non_targets[0], piece };
    Move const unexpected_move2{ source, non_targets[1], piece };

    EXPECT_TRUE(std::ranges::contains(moves, expected_move1));
    EXPECT_TRUE(std::ranges::contains(moves, expected_move2));
    EXPECT_FALSE(std::ranges::contains(moves, unexpected_move1));
    EXPECT_FALSE(std::ranges::contains(moves, unexpected_move2));
    EXPECT_EQ(moves.size(), 3); // includes push
}

TEST(Search, PawnCaptureBlack)
{
    auto const piece = Piece::Pawn;
    auto const side = Side::Black;
    auto const opponent_side = Side::White;
    auto const source = Square::D5;
    std::array const targets{ Square::C4, Square::E4 };
    std::array const non_targets{ Square::C6, Square::E6 };
    auto const game = [=] {
        GameBuilder game_builder;
        game_builder.set_square(piece, side, source);
        auto const set_square = [&game_builder](auto t) { game_builder.set_square(piece, opponent_side, t); };
        std::ranges::for_each(targets, set_square);
        std::ranges::for_each(non_targets, set_square);
        game_builder.set_to_move(side);
        return game_builder.build();
    }();
    auto const moves = search::find_moves(game);
    Move const expected_move1{ source, targets[0], piece };
    Move const expected_move2{ source, targets[1], piece };
    Move const unexpected_move1{ source, non_targets[0], piece };
    Move const unexpected_move2{ source, non_targets[1], piece };

    EXPECT_TRUE(std::ranges::contains(moves, expected_move1));
    EXPECT_TRUE(std::ranges::contains(moves, expected_move2));
    EXPECT_FALSE(std::ranges::contains(moves, unexpected_move1));
    EXPECT_FALSE(std::ranges::contains(moves, unexpected_move2));
    EXPECT_EQ(moves.size(), 3); // includes push
}
