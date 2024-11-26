#pragma once

#ifndef ARCHIVE_COMMON_UTILITY_HPP
#define ARCHIVE_COMMON_UTILITY_HPP

namespace archive::utility
{
    template<typename... Args>
    inline constexpr auto ignore(Args&&... args) -> void
    {
        (static_cast<void>(args), ...);
    }
} // namespace archive::utility

#endif // ARCHIVE_COMMON_UTILITY_HPP
