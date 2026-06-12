#ifndef CHESSLIB_PIECE_HPP
#define CHESSLIB_PIECE_HPP

#include "seblib/enum.hpp"

#include <array>
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

// *********************************************************************************************************************
//                                             INLINE & TEMPLATE DEFINITIONS
// *********************************************************************************************************************

// temporary until clang++ supports reflection
#ifdef __clang__
namespace seb::enumerator
{
using namespace chess;

template <>
consteval auto vals<Piece>()
{
    return std::array{
        Piece::Pawn, Piece::Knight, Piece::Bishop, Piece::Rook, Piece::Queen, Piece::King,
    };
}
} // namespace seb::enumerator
#endif

#endif
