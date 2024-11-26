#include "archive/frontend/source.hpp"
#include "archive/common/utility.hpp"

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

auto Source::is_at_end() const -> bool
{
    return m_cursor >= m_text.size();
}

auto Source::peek() const -> std::optional<char>
{
    return (!is_at_end())
         ? std::make_optional(m_text[m_cursor])
         : std::nullopt;
}

auto Source::peek(const char chr) const -> std::optional<char>
{
    const auto current = peek();
    return (current == chr)
         ? current
         : std::nullopt;
}

auto Source::peek(const std::string_view str) const -> std::optional<std::string_view>
{
    if (is_at_end())
        return std::nullopt;

    const auto current = std::string_view(m_text).substr(m_cursor, str.size());
    return (current == str)
         ? std::make_optional(current)
         : std::nullopt;
}

auto Source::operator++() -> std::optional<char>
{
    utility::ignore(consume());
    return peek();
}

auto Source::operator++(int) -> std::optional<char>
{
    return consume();
}

auto Source::consume() -> std::optional<char>
{
    const auto current = peek();
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
    return peek(chr)
         ? consume()
         : std::nullopt;
}

auto Source::consume(const std::string_view str) -> std::optional<std::string_view>
{
    const auto current = peek(str);
    const auto chars   = (current) ? *current : std::string_view("");

    for (const auto& _ [[maybe_unused]]: chars)
        utility::ignore(consume());

    return current;
}
