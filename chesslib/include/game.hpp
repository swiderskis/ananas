#ifndef CHESSLIB_GAME_HPP
#define CHESSLIB_GAME_HPP

#include <cstddef>
#include <cstdint>

namespace chess
{
// clang-format off
enum class Square
{
    A8, B8, C8, D8, E8, F8, G8, H8,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A1, B1, C1, D1, E1, F1, G1, H1,
};
// clang-format on

enum class Piece
{
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
};

enum class Side
{
    White,
    Black,
};

class Bitboard
{
public:
    [[nodiscard]] constexpr auto board() const -> uint64_t { return board_; }

    constexpr auto operator|=(Square square) -> void { board_ |= 1uz << static_cast<size_t>(square); }
    constexpr auto operator^=(Square square) -> void { board_ &= ~(1uz << static_cast<size_t>(square)); }

private:
    uint64_t board_{ 0 };
};

class Game
{
public:
    Game();

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
};
} // namespace chess

#endif
