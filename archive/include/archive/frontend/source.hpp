#pragma once

#ifndef ARCHIVE_FRONTEND_SOURCE_HPP
#define ARCHIVE_FRONTEND_SOURCE_HPP

#include <string>
#include <cstdint>
#include <cstddef>
#include <optional>

#include "archive/frontend/location.hpp"

namespace archive::frontend
{
    class Source final
    {
    public:
        explicit Source(std::string text = "");

        [[nodiscard]] auto location()  const -> const Location&;
        [[nodiscard]] auto is_at_end() const -> bool;

        [[nodiscard]] auto peek()                           const -> std::optional<char>;
        [[nodiscard]] auto peek(const char             chr) const -> std::optional<char>;
        [[nodiscard]] auto peek(const std::string_view str) const -> std::optional<std::string_view>;

        [[nodiscard]] auto operator++()    -> std::optional<char>;
        [[nodiscard]] auto operator++(int) -> std::optional<char>;

        [[nodiscard]] auto consume()                           -> std::optional<char>;
        [[nodiscard]] auto consume(const char             chr) -> std::optional<char>;
        [[nodiscard]] auto consume(const std::string_view str) -> std::optional<std::string_view>;

        [[nodiscard]] auto consume_escape_char() -> char;

    private:
        Location    m_location;
        std::size_t m_cursor;
        std::string m_text;
    };
} // namespace archive::frontend

#endif // ARCHIVE_FRONTEND_SOURCE_HPP
