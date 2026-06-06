#ifndef CHESSLIB_PIECE_HPP
#define CHESSLIB_PIECE_HPP

#include <cstdint>

namespace chess
{
enum class Piece : uint8_t
{
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
};
} // namespace chess

#endif
