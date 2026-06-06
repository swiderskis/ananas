#ifndef CHESSLIB_SEARCH_HPP
#define CHESSLIB_SEARCH_HPP

#include "chesslib/game.hpp"
#include "chesslib/move.hpp"

#include <vector>

namespace chess::search
{
auto find_moves(Game game) -> std::vector<Move>;
} // namespace chess::search

#endif
