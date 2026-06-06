#ifndef CHESSLIB_MOVE_HPP
#define CHESSLIB_MOVE_HPP

#include "chesslib/piece.hpp"
#include "chesslib/square.hpp"

namespace chess
{
struct Move
{
    Square source;
    Square target;
    Piece piece;

    Move(Square source, Square target, Piece piece);

    auto operator==(Move const & move) const -> bool = default;
};
} // namespace chess

#endif
