#ifndef CHESSLIB_SQUARE_HPP
#define CHESSLIB_SQUARE_HPP

#include <algorithm>
#include <array>
#include <cstdint>
#include <inplace_vector>
#include <meta>
#include <optional>
#include <ranges>
#include <type_traits>
#include <utility>

namespace chess
{
// clang-format off
enum class Square : uint8_t
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

enum class Rank : uint8_t
{
    Eight,
    Seven,
    Six,
    Five,
    Four,
    Three,
    Two,
    One,
};

enum class File : uint8_t
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
};

enum class Dir : uint8_t
{
    NW,
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
};

enum class KnightDir : uint8_t
{
    NNW,
    NNE,
    ENE,
    ESE,
    SSE,
    SSW,
    WSW,
    WNW,
};

namespace square
{
constexpr auto is_in(Square square, Rank rank) -> bool;
constexpr auto is_in(Square square, File file) -> bool;
constexpr auto at(Square square, Dir dir) -> std::optional<Square>;
constexpr auto at(Square square, KnightDir dir) -> std::optional<Square>;

// *********************************************************************************************************************
//                                             INLINE & TEMPLATE DEFINITIONS
// *********************************************************************************************************************

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

constexpr auto is_in(Square square, Rank rank) -> bool
{
    // TODO reflection ;)
    static constexpr std::array squares{
        Square::A8, Square::B8, Square::C8, Square::D8, Square::E8, Square::F8, Square::G8, Square::H8,
        Square::A7, Square::B7, Square::C7, Square::D7, Square::E7, Square::F7, Square::G7, Square::H7,
        Square::A6, Square::B6, Square::C6, Square::D6, Square::E6, Square::F6, Square::G6, Square::H6,
        Square::A5, Square::B5, Square::C5, Square::D5, Square::E5, Square::F5, Square::G5, Square::H5,
        Square::A4, Square::B4, Square::C4, Square::D4, Square::E4, Square::F4, Square::G4, Square::H4,
        Square::A3, Square::B3, Square::C3, Square::D3, Square::E3, Square::F3, Square::G3, Square::H3,
        Square::A2, Square::B2, Square::C2, Square::D2, Square::E2, Square::F2, Square::G2, Square::H2,
        Square::A1, Square::B1, Square::C1, Square::D1, Square::E1, Square::F1, Square::G1, Square::H1,
    };

    auto const in_rank = [rank](auto s) {
        auto const min = std::to_underlying(rank) * 8;
        auto const max = min + 7;
        return std::to_underlying(s) >= min && std::to_underlying(s) <= max;
    };
    auto const rank_squares = squares | std::views::filter(in_rank) | std::ranges::to<std::inplace_vector<Square, 8>>();

    return std::ranges::contains(rank_squares, square);
}

constexpr auto is_in(Square square, File file) -> bool
{
    // TODO reflection ;)
    static constexpr std::array squares{
        Square::A8, Square::B8, Square::C8, Square::D8, Square::E8, Square::F8, Square::G8, Square::H8,
        Square::A7, Square::B7, Square::C7, Square::D7, Square::E7, Square::F7, Square::G7, Square::H7,
        Square::A6, Square::B6, Square::C6, Square::D6, Square::E6, Square::F6, Square::G6, Square::H6,
        Square::A5, Square::B5, Square::C5, Square::D5, Square::E5, Square::F5, Square::G5, Square::H5,
        Square::A4, Square::B4, Square::C4, Square::D4, Square::E4, Square::F4, Square::G4, Square::H4,
        Square::A3, Square::B3, Square::C3, Square::D3, Square::E3, Square::F3, Square::G3, Square::H3,
        Square::A2, Square::B2, Square::C2, Square::D2, Square::E2, Square::F2, Square::G2, Square::H2,
        Square::A1, Square::B1, Square::C1, Square::D1, Square::E1, Square::F1, Square::G1, Square::H1,
    };

    auto const in_file = [file](auto s) { return std::to_underlying(s) % 8 == std::to_underlying(file); };
    auto const file_squares = squares | std::views::filter(in_file) | std::ranges::to<std::inplace_vector<Square, 8>>();

    return std::ranges::contains(file_squares, square);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

constexpr auto at(Square square, Dir dir) -> std::optional<Square>
{
    auto const square_conversion =
        [square](int32_t adjustment, std::optional<Rank> excl_rank, std::optional<File> excl_file) {
            auto const excluded_rank = excl_rank.has_value() && square::is_in(square, excl_rank.value());
            auto const excluded_file = excl_file.has_value() && square::is_in(square, excl_file.value());
            auto const square_idx = std::to_underlying(square);
            return (excluded_rank || excluded_file ? std::nullopt
                                                   : std::make_optional(static_cast<Square>(square_idx + adjustment)));
        };

    switch (dir) {
    case Dir::NW:
        return square_conversion(-9, Rank::Eight, File::A);
    case Dir::N:
        return square_conversion(-8, Rank::Eight, std::nullopt);
    case Dir::NE:
        return square_conversion(-7, Rank::Eight, File::H);
    case Dir::E:
        return square_conversion(1, std::nullopt, File::H);
    case Dir::SE:
        return square_conversion(9, Rank::One, File::H);
    case Dir::S:
        return square_conversion(8, Rank::One, std::nullopt);
    case Dir::SW:
        return square_conversion(7, Rank::One, File::A);
    case Dir::W:
        return square_conversion(-1, std::nullopt, File::A);
    }

    std::unreachable();
}

constexpr auto at(Square square, KnightDir dir) -> std::optional<Square>
{
    auto const square_conversion =
        [square]<typename Ranks, typename Files>(int32_t adjustment, Ranks excl_ranks, Files excl_files) {
            auto const excluded_rank
                = std::ranges::any_of(excl_ranks, [square](auto r) { return square::is_in(square, r); });
            auto const excluded_file
                = std::ranges::any_of(excl_files, [square](auto f) { return square::is_in(square, f); });
            auto const square_idx = std::to_underlying(square);
            return (excluded_rank || excluded_file ? std::nullopt
                                                   : std::make_optional(static_cast<Square>(square_idx + adjustment)));
        };

    switch (dir) {
    case KnightDir::NNW:
        return square_conversion(-17, std::array{ Rank::Seven, Rank::Eight }, std::array{ File::A });
    case KnightDir::NNE:
        return square_conversion(-15, std::array{ Rank::Seven, Rank::Eight }, std::array{ File::H });
    case KnightDir::ENE:
        return square_conversion(-6, std::array{ Rank::Eight }, std::array{ File::G, File::H });
    case KnightDir::ESE:
        return square_conversion(10, std::array{ Rank::One }, std::array{ File::G, File::H });
    case KnightDir::SSE:
        return square_conversion(17, std::array{ Rank::One, Rank::Two }, std::array{ File::H });
    case KnightDir::SSW:
        return square_conversion(15, std::array{ Rank::One, Rank::Two }, std::array{ File::A });
    case KnightDir::WSW:
        return square_conversion(6, std::array{ Rank::One }, std::array{ File::A, File::B });
    case KnightDir::WNW:
        return square_conversion(-10, std::array{ Rank::Eight }, std::array{ File::A, File::B });
    }

    std::unreachable();
}
} // namespace square
} // namespace chess

#endif
