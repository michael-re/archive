#include "archive/frontend/source.hpp"

using namespace archive;
using namespace archive::frontend;

Source::Source(std::string text)
    : m_location({ 1, 1 }),
      m_cursor  (0),
      m_text    (std::move(text))
{
}

auto Source::location() const -> const Location&
{
    return m_location;
}

auto Source::operator[](const int idx) const -> std::optional<char>
{
    const auto cursor = m_cursor + static_cast<std::size_t>(idx);
    return (cursor < m_text.size())
         ? std::make_optional(m_text[cursor])
         : std::nullopt;
}

auto Source::operator[](const char chr) const -> std::optional<char>
{
    const auto current = (*this)[0];
    return (current == chr)
         ? current
         : std::nullopt;
}

auto Source::operator[](const std::string_view str) const -> std::optional<std::string_view>
{
    const auto current = std::string_view(m_text).substr(m_cursor, str.size());
    return (current == str)
         ? std::make_optional(current)
         : std::nullopt;
}

auto Source::operator++() -> std::optional<char>
{
    static_cast<void>(consume());
    return (*this)[0];
}

auto Source::operator++(int) -> std::optional<char>
{
    return consume();
}

auto Source::consume() -> std::optional<char>
{
    const auto current = (*this)[0];
    if (current == '\n')
    {
        m_location.line++;
        m_location.column = 0;
    }

    if (current != std::nullopt)
    {
        m_cursor++;
        m_location.column++;
    }

    return current;
}

auto Source::consume(const char chr) -> std::optional<char>
{
    return ((*this)[chr])
         ? consume()
         : std::nullopt;
}

auto Source::consume(const std::string_view str) -> std::optional<std::string_view>
{
    const auto current = (*this)[str];
    const auto chars   = (current) ? *current : std::string_view("");

    for (const auto& _ [[maybe_unused]]: chars)
        static_cast<void>(consume());

    return current;
}
