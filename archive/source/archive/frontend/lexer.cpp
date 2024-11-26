#include "archive/frontend/lexer.hpp"
#include "archive/common/utility.hpp"

using namespace archive;
using namespace archive::frontend;

Lexer::Lexer(std::string source)
    : m_source(std::move(source))
{
}

auto Lexer::lex() -> Token
{
    const auto current  = lex_whitespace();
    const auto location = m_source.location();

    utility::ignore(m_source++);
    return (!current)
         ? Token(Token::Type::EndOfFile, location)
         : Token(Token::Type::Unknown,   location, { *current, '\0' });
}

auto Lexer::lex_whitespace() -> std::optional<char>
{
    while (lex_nonprintable() || lex_comments())
    {
        // skip non printable characters and comments
    }

    return m_source.peek();
}

auto Lexer::lex_nonprintable() -> bool
{
    // whitespace - any non printable ascii characters + space (' ')
    if (!m_source.is_at_end() && m_source.peek() <= 0x20)
    {
        utility::ignore(m_source++);
        return true;
    }

    return false;
}

auto Lexer::lex_comments() -> bool
{
    // single-line comments
    if (!m_source.is_at_end() && m_source.consume("//"))
    {
        while (!m_source.is_at_end() && !m_source.consume('\n'))
            utility::ignore(m_source++);
        return true;
    }

    // multi-line comments
    if (!m_source.is_at_end() && m_source.consume("/*"))
    {
        while (!m_source.is_at_end() && !m_source.consume("*/"))
            utility::ignore(m_source++);
        return true;
    }

    return false;
}
