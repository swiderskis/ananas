#include "chesslib/move.hpp"

using namespace chess;

Move::Move(Square source, Square target, Piece piece)
    : source{ source }
    , target{ target }
    , piece{ piece }
{
}
