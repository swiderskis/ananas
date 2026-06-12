#include "chesslib/game.hpp"

#include "chesslib/piece.hpp"

#include <optional>
#include <ranges>
#include <tuple>
#include <utility>

using namespace chess;

namespace sebenum = seb::enumerator;

Game::Game(StartPosT /*start_pos*/)
{
    white_pawns_ |= Square::A2;
    white_pawns_ |= Square::B2;
    white_pawns_ |= Square::C2;
    white_pawns_ |= Square::D2;
    white_pawns_ |= Square::E2;
    white_pawns_ |= Square::F2;
    white_pawns_ |= Square::G2;
    white_pawns_ |= Square::H2;

    white_knights_ |= Square::B1;
    white_knights_ |= Square::G1;

    white_bishops_ |= Square::C1;
    white_bishops_ |= Square::F1;

    white_rooks_ |= Square::A1;
    white_rooks_ |= Square::H1;

    white_queens_ |= Square::D1;

    white_king_ |= Square::E1;

    black_pawns_ |= Square::A7;
    black_pawns_ |= Square::B7;
    black_pawns_ |= Square::C7;
    black_pawns_ |= Square::D7;
    black_pawns_ |= Square::E7;
    black_pawns_ |= Square::F7;
    black_pawns_ |= Square::G7;
    black_pawns_ |= Square::H7;

    black_knights_ |= Square::B8;
    black_knights_ |= Square::G8;

    black_bishops_ |= Square::C8;
    black_bishops_ |= Square::F8;

    black_rooks_ |= Square::A8;
    black_rooks_ |= Square::H8;

    black_queens_ |= Square::D8;

    black_king_ |= Square::E8;
}

auto Game::at(Square square) const -> std::optional<std::tuple<Piece, Side>>
{
    auto board_view = std::views::cartesian_product(sebenum::vals<Piece>(), sebenum::vals<Side>())
        | std::views::drop_while([&](auto v) { return !board(std::get<0>(v), std::get<1>(v)).is_set(square); });

    return (board_view.empty() ? std::nullopt : std::make_optional(*board_view.begin()));
}

auto Game::board(Piece piece, Side side) const -> Bitboard
{
    switch (side) {
    case Side::White:
        switch (piece) {
        case Piece::Pawn:
            return white_pawns_;
        case Piece::Knight:
            return white_knights_;
        case Piece::Bishop:
            return white_bishops_;
        case Piece::Rook:
            return white_rooks_;
        case Piece::Queen:
            return white_queens_;
        case Piece::King:
            return white_king_;
        }
        break;
    case Side::Black:
        switch (piece) {
        case Piece::Pawn:
            return black_pawns_;
        case Piece::Knight:
            return black_knights_;
        case Piece::Bishop:
            return black_bishops_;
        case Piece::Rook:
            return black_rooks_;
        case Piece::Queen:
            return black_queens_;
        case Piece::King:
            return black_king_;
        }
        break;
    }

    std::unreachable();
}

auto Game::board(Side side) const -> Bitboard
{
    switch (side) {
    case Side::White:
        return white_pawns_ | white_knights_ | white_bishops_ | white_rooks_ | white_queens_ | white_king_;
    case Side::Black:
        return black_pawns_ | black_knights_ | black_bishops_ | black_rooks_ | black_queens_ | black_king_;
    }

    std::unreachable();
}

auto Game::board_mut(Piece piece, Side side) -> Bitboard &
{
    switch (side) {
    case Side::White:
        switch (piece) {
        case Piece::Pawn:
            return white_pawns_;
        case Piece::Knight:
            return white_knights_;
        case Piece::Bishop:
            return white_bishops_;
        case Piece::Rook:
            return white_rooks_;
        case Piece::Queen:
            return white_queens_;
        case Piece::King:
            return white_king_;
        }
        break;
    case Side::Black:
        switch (piece) {
        case Piece::Pawn:
            return black_pawns_;
        case Piece::Knight:
            return black_knights_;
        case Piece::Bishop:
            return black_bishops_;
        case Piece::Rook:
            return black_rooks_;
        case Piece::Queen:
            return black_queens_;
        case Piece::King:
            return black_king_;
        }
        break;
    }

    std::unreachable();
}
