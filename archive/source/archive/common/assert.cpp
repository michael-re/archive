#include <format>

#include "archive/common/assert.hpp"
#include "archive/common/excode.hpp"

using namespace archive;
using namespace archive::assert;

auto assert::error(const std::string_view     expression,
                   const std::string_view     message,
                   const std::source_location location) -> Fatal
{
    const auto reason = expression.empty() ? "(empty assert expression)" : expression;
    return message.empty()
         ? Fatal(std::format("assertion failed: {}", reason), location)
         : Fatal(std::format("assertion failed: {}\n{}", reason, message), location);
}

auto assert::terminate(const std::string_view     expression,
                       const std::string_view     message,
                       const std::source_location location) -> void
{
    error(expression, message, location).terminate();
}
