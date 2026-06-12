#ifndef SEBLIB_ENUM_HPP
#define SEBLIB_ENUM_HPP

#include <meta>
#include <type_traits>
#ifndef __clang__
#include <vector>
#endif

namespace seb
{
template <typename Enum>
concept Enumerable = std::is_enum_v<Enum> || std::is_scoped_enum_v<Enum>;

namespace enumerator
{
template <Enumerable Enum>
consteval auto vals();

// *********************************************************************************************************************
//                                             INLINE & TEMPLATE DEFINITIONS
// *********************************************************************************************************************

#ifndef __clang__
template <Enumerable Enum>
consteval auto vals()
{
    // clang-format off
    // TODO make this work with ranges & views
    std::vector<Enum> vals;
    template for (constexpr auto e : std::define_static_array(std::meta::enumerators_of(^^Enum))) {
        vals.push_back([:e:]);
    }
    // clang-format on

    return std::define_static_array(vals);
}
#endif
} // namespace enumerator
} // namespace seb

#endif
