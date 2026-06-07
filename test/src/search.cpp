#include "chesslib/search.hpp"

#include "chesslib/game.hpp"
#include "chesslib/piece.hpp"
#include "chesslib/square.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <inplace_vector>
#include <ranges>

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

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

TEST(Search, KnightMoves)
{
    auto const knight_test = []<typename Targets>(Square source, Targets targets) {
        auto const piece = Piece::Knight;
        auto const side = Side::White;
        auto const game = [=]() {
            GameBuilder game_builder;
            game_builder.set_square(piece, side, source);
            return game_builder.build();
        }();
        auto const moves = search::find_moves(game);
        auto const expected_moves = targets
            | std::views::transform([source](auto t) { return Move{ source, t, piece }; })
            | std::ranges::to<std::inplace_vector<Move, targets.size()>>();
        EXPECT_TRUE(std::ranges::all_of(expected_moves, [moves](auto m) { return std::ranges::contains(moves, m); }));
    };

    knight_test(
        Square::E4,
        std::array{ Square::D6, Square::F6, Square::G5, Square::G3, Square::F2, Square::D2, Square::C3, Square::C5 });
    knight_test(Square::A8, std::array{ Square::C7, Square::B6 });
    knight_test(Square::B7, std::array{ Square::D8, Square::D6, Square::C5, Square::A5 });
    knight_test(Square::E8, std::array{ Square::G7, Square::F6, Square::D6, Square::C7 });
    knight_test(Square::E7, std::array{ Square::G8, Square::G6, Square::F5, Square::D5, Square::C6, Square::C8 });
    knight_test(Square::H8, std::array{ Square::G6, Square::F7 });
    knight_test(Square::G7, std::array{ Square::H5, Square::F5, Square::E6, Square::E8 });
    knight_test(Square::H4, std::array{ Square::G2, Square::F3, Square::F5, Square::G6 });
    knight_test(Square::G4, std::array{ Square::H2, Square::F2, Square::E3, Square::E5, Square::F6, Square::H6 });
    knight_test(Square::H1, std::array{ Square::F2, Square::G3 });
    knight_test(Square::G2, std::array{ Square::E1, Square::E3, Square::F4, Square::H4 });
    knight_test(Square::E1, std::array{ Square::C2, Square::D3, Square::F3, Square::G2 });
    knight_test(Square::E2, std::array{ Square::C1, Square::C3, Square::D4, Square::F4, Square::G3, Square::G1 });
    knight_test(Square::A1, std::array{ Square::B3, Square::C2 });
    knight_test(Square::B2, std::array{ Square::A4, Square::C4, Square::D3, Square::D1 });
    knight_test(Square::A4, std::array{ Square::B6, Square::C5, Square::C3, Square::B2 });
    knight_test(Square::B4, std::array{ Square::A6, Square::C6, Square::D5, Square::D3, Square::C2, Square::A2 });
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
