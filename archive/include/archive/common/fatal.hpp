#pragma once

#ifndef ARCHIVE_COMMON_FATAL_HPP
#define ARCHIVE_COMMON_FATAL_HPP

#include <string_view>
#include <source_location>

#include "archive/common/except.hpp"

namespace archive
{
    class Fatal final : public Exception
    {
    public:
        explicit Fatal(const std::string_view     message  = "",
                       const std::source_location location =
                             std::source_location::current()) noexcept;

        [[noreturn]] auto terminate() const -> void;
    };
} // namespace archive

#endif // ARCHIVE_COMMON_FATAL_HPP
