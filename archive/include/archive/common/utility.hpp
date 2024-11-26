#pragma once

#ifndef ARCHIVE_COMMON_UTILITY_HPP
#define ARCHIVE_COMMON_UTILITY_HPP

#include <concepts>
#include <type_traits>

namespace archive::utility
{
    template<typename... Args>
    inline constexpr auto ignore(Args&&... args) -> void
    {
        (static_cast<void>(args), ...);
    }

    template<std::integral C>
    [[nodiscard]] constexpr auto is_squote(const C c) -> bool
    {
        return (static_cast<C>('\'') == c);
    }

    template<std::integral C>
    [[nodiscard]] constexpr auto is_dquote(const C c) -> bool
    {
        return (static_cast<C>('"') == c);
    }

    template<std::integral C>
    [[nodiscard]] constexpr auto is_digit(const C c) -> bool
    {
        return (static_cast<C>('0') <= c && c <= static_cast<C>('9'));
    }

    template<std::integral C>
    [[nodiscard]] constexpr auto is_hex_digit(const C c) -> bool
    {
        return (static_cast<C>('A') <= c && c <= static_cast<C>('F')) ||
               (static_cast<C>('a') <= c && c <= static_cast<C>('f')) ||
               is_digit(c);
    }
} // namespace archive::utility

#endif // ARCHIVE_COMMON_UTILITY_HPP
