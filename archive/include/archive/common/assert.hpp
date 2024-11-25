#pragma once

#ifndef ARCHIVE_COMMON_ASSERT_HPP
#define ARCHIVE_COMMON_ASSERT_HPP

#include "archive/common/except.hpp"
#include "archive/common/fatal.hpp"

namespace archive::assert
{
    [[nodiscard]] auto error(const std::string_view     expression = "",
                             const std::string_view     message    = "",
                             const std::source_location location   =
                                   std::source_location::current()) -> Fatal;

    [[noreturn]] auto terminate(const std::string_view     expression = "",
                                const std::string_view     message    = "",
                                const std::source_location location   =
                                      std::source_location::current()) -> void;
} // namespace archive::assert

#define ASSERT(expression, ...)                                     \
    do                                                              \
    {                                                               \
        if (!(expression))                                          \
            archive::assert::terminate(#expression, ##__VA_ARGS__); \
    } while (0)                                                     \

#define FATAL(message)                       \
    do                                       \
    {                                        \
        archive::Fatal(message).terminate(); \
    } while (0)                              \

#endif // ARCHIVE_COMMON_ASSERT_HPP
