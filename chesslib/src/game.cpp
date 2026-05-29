#include "game.hpp"

using namespace chess;

Game::Game()
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
