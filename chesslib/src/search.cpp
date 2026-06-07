#include "chesslib/search.hpp"

#include "chesslib/game.hpp"
#include "chesslib/piece.hpp"
#include "chesslib/square.hpp"

#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

using namespace chess;

namespace
{
// TODO reflection ;)
constexpr std::array SQUARES{
    Square::A8, Square::B8, Square::C8, Square::D8, Square::E8, Square::F8, Square::G8, Square::H8,
    Square::A7, Square::B7, Square::C7, Square::D7, Square::E7, Square::F7, Square::G7, Square::H7,
    Square::A6, Square::B6, Square::C6, Square::D6, Square::E6, Square::F6, Square::G6, Square::H6,
    Square::A5, Square::B5, Square::C5, Square::D5, Square::E5, Square::F5, Square::G5, Square::H5,
    Square::A4, Square::B4, Square::C4, Square::D4, Square::E4, Square::F4, Square::G4, Square::H4,
    Square::A3, Square::B3, Square::C3, Square::D3, Square::E3, Square::F3, Square::G3, Square::H3,
    Square::A2, Square::B2, Square::C2, Square::D2, Square::E2, Square::F2, Square::G2, Square::H2,
    Square::A1, Square::B1, Square::C1, Square::D1, Square::E1, Square::F1, Square::G1, Square::H1,
};

auto find_pawn_moves(std::vector<Move> && moves, Game game) -> std::vector<Move>;
auto find_pawn_single_push(std::vector<Move> && moves, Game game) -> std::vector<Move>;
auto find_pawn_double_push(std::vector<Move> && moves, Game game) -> std::vector<Move>;
auto find_pawn_captures(std::vector<Move> && moves, Game game) -> std::vector<Move>;
auto find_knight_moves(std::vector<Move> && moves, Game game) -> std::vector<Move>;
auto find_king_moves(std::vector<Move> && moves, Game game) -> std::vector<Move>;
} // namespace

auto search::find_moves(Game game) -> std::vector<Move>
{
    static_assert(std::is_nothrow_move_constructible_v<Move>);

    std::vector<Move> moves;
    moves = find_pawn_moves(std::move(moves), game);

    return moves;
}

namespace
{
auto find_pawn_moves(std::vector<Move> && moves, Game game) -> std::vector<Move>
{
    moves = find_pawn_single_push(std::move(moves), game);
    moves = find_pawn_double_push(std::move(moves), game);
    moves = find_pawn_captures(std::move(moves), game);
    moves = find_knight_moves(std::move(moves), game);
    moves = find_king_moves(std::move(moves), game);

    return std::move(moves);
}

auto find_pawn_single_push(std::vector<Move> && moves, Game game) -> std::vector<Move>
{
    auto const push_dir = (game.to_move() == Side::White ? Dir::N : Dir::S);
    auto const pawn_board = game.board(Piece::Pawn, game.to_move());
    auto pawn_moves = SQUARES
        | std::views::filter([pawn_board](auto s) { return pawn_board.is_set(s); })
        | std::views::transform([push_dir](auto s) { return std::make_pair(s, square::at(s, push_dir)); })
        | std::views::filter([](auto m) { return m.second.has_value(); })
        | std::views::transform([](auto m) { return Move{ m.first, m.second.value(), Piece::Pawn }; });
    moves.insert_range(moves.end(), pawn_moves);

    return std::move(moves);
}

auto find_pawn_double_push(std::vector<Move> && moves, Game game) -> std::vector<Move>
{
    auto const push_dir = (game.to_move() == Side::White ? Dir::N : Dir::S);
    auto const start_rank = (game.to_move() == Side::White ? Rank::Two : Rank::Seven);
    auto const pawn_board = game.board(Piece::Pawn, game.to_move());
    auto const get_target = [push_dir](auto s) {
        auto const single_push = square::at(s, push_dir).value();
        auto const target = square::at(single_push, push_dir).value();
        return std::make_pair(s, target);
    };
    auto pawn_moves = SQUARES
        | std::views::filter([pawn_board](auto s) { return pawn_board.is_set(s); })
        | std::views::filter([start_rank](auto s) { return square::is_in(s, start_rank); })
        | std::views::transform(get_target)
        | std::views::transform([](auto m) { return Move{ m.first, m.second, Piece::Pawn }; });
    moves.insert_range(moves.end(), pawn_moves);

    return std::move(moves);
}

auto find_pawn_captures(std::vector<Move> && moves, Game game) -> std::vector<Move>
{
    auto const capture_dirs
        = (game.to_move() == Side::White ? std::array{ Dir::NW, Dir::NE } : std::array{ Dir::SW, Dir::SE });
    auto const pawn_board = game.board(Piece::Pawn, game.to_move());
    auto const opponent_side = (game.to_move() == Side::White ? Side::Black : Side::White);
    auto const opponent_board = game.board(opponent_side);
    auto const get_targets_view = [capture_dirs](auto s) {
        return capture_dirs
            | std::views::transform([s](auto d) { return std::make_pair(s, square::at(s, d)); })
            | std::views::filter([](auto m) { return m.second.has_value(); });
    };
    auto pawn_moves = SQUARES
        | std::views::filter([pawn_board](auto s) { return pawn_board.is_set(s); })
        | std::views::transform(get_targets_view)
        | std::views::join
        | std::views::filter([opponent_board](auto m) { return opponent_board.is_set(m.second.value()); })
        | std::views::transform([](auto m) { return Move{ m.first, m.second.value(), Piece::Pawn }; });
    moves.insert_range(moves.end(), pawn_moves);

    return std::move(moves);
}

auto find_knight_moves(std::vector<Move> && moves, Game game) -> std::vector<Move>
{
    // TODO reflection ;)
    static constexpr std::array knight_dirs{ KnightDir::NNW, KnightDir::NNE, KnightDir::ENE, KnightDir::ESE,
                                             KnightDir::SSE, KnightDir::SSW, KnightDir::WSW, KnightDir::WNW };
    auto const knight_board = game.board(Piece::Knight, game.to_move());
    auto const get_targets_view = [](auto s) {
        return knight_dirs
            | std::views::transform([s](auto d) { return std::make_pair(s, square::at(s, d)); })
            | std::views::filter([](auto m) { return m.second.has_value(); });
    };
    auto knight_moves = SQUARES
        | std::views::filter([knight_board](auto s) { return knight_board.is_set(s); })
        | std::views::transform(get_targets_view)
        | std::views::join
        | std::views::transform([](auto m) { return Move{ m.first, m.second.value(), Piece::Knight }; });
    moves.insert_range(moves.end(), knight_moves);

    return std::move(moves);
}

auto find_king_moves(std::vector<Move> && moves, Game game) -> std::vector<Move>
{
    // TODO reflection ;)
    static constexpr std::array dirs{ Dir::NW, Dir::N, Dir::NE, Dir::E, Dir::SE, Dir::S, Dir::SW, Dir::W };
    auto const king_board = game.board(Piece::King, game.to_move());
    auto const get_targets_view = [](auto s) {
        return dirs
            | std::views::transform([s](auto d) { return std::make_pair(s, square::at(s, d)); })
            | std::views::filter([](auto m) { return m.second.has_value(); });
    };
    auto king_moves = SQUARES
        | std::views::filter([king_board](auto s) { return king_board.is_set(s); })
        | std::views::transform(get_targets_view)
        | std::views::join
        | std::views::transform([](auto m) { return Move{ m.first, m.second.value(), Piece::King }; });
    moves.insert_range(moves.end(), king_moves);

    return std::move(moves);
}
} // namespace
