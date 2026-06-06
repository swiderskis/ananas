#ifndef CHESSLIB_GAME_HPP
#define CHESSLIB_GAME_HPP

#include "chesslib/move.hpp"
#include "chesslib/square.hpp"

#include <cstdint>
#include <optional>
#include <tuple>
#include <utility>

namespace chess
{
enum class Side : uint8_t
{
    White,
    Black,
};

class Bitboard
{
public:
    [[nodiscard]] constexpr auto board() const -> uint64_t { return board_; }
    [[nodiscard]] constexpr auto is_set(Square square) const -> bool;

    constexpr auto operator|=(Square square) -> void { board_ |= 1uz << std::to_underlying(square); }
    constexpr auto operator^=(Square square) -> void { board_ &= ~(1uz << std::to_underlying(square)); }

private:
    uint64_t board_{ 0 };
};

class GameBuilder;

class Game
{
public:
    // clang-format off
    static constexpr struct StartPosT{} StartPos{}; // NOLINT(readability-identifier-naming)
    // clang-format on

    Game() = default;
    Game(StartPosT /*start_pos*/);

    auto make_move(Move move) -> void;
    [[nodiscard]] auto at(Square square) const -> std::optional<std::tuple<Piece, Side>>;
    [[nodiscard]] auto board(Piece piece, Side side) const -> Bitboard;
    [[nodiscard]] auto to_move() const -> Side { return to_move_; }

    friend class GameBuilder;

private:
    auto board_mut(Piece piece, Side side) -> Bitboard &;

private:
    Bitboard white_pawns_;
    Bitboard white_knights_;
    Bitboard white_bishops_;
    Bitboard white_rooks_;
    Bitboard white_queens_;
    Bitboard white_king_;
    Bitboard black_pawns_;
    Bitboard black_knights_;
    Bitboard black_bishops_;
    Bitboard black_rooks_;
    Bitboard black_queens_;
    Bitboard black_king_;
    Side to_move_{ Side::White };
};

class GameBuilder
{
public:
    auto set_square(Piece piece, Side side, Square square) -> void { game_.board_mut(piece, side) |= square; }
    auto set_to_move(Side side) -> void { game_.to_move_ = side; }
    auto build() -> Game { return game_; }

private:
    Game game_;
};

// *********************************************************************************************************************
//                                             INLINE & TEMPLATE DEFINITIONS
// *********************************************************************************************************************

constexpr auto Bitboard::is_set(Square square) const -> bool
{
    return (board_ & 1uz << std::to_underlying(square)) != 0;
}
} // namespace chess

#endif
