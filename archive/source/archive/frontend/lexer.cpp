#include "archive/frontend/lexer.hpp"
#include "archive/common/utility.hpp"
#include "archive/common/assert.hpp"

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
    if (!current)
        return { Token::Type::EndOfFile, location };

    const auto character = *current;
    if (character == '\'') return lex_character();

    utility::ignore(m_source++);
    return { Token::Type::Error, location, "unexpected character" };
}

auto Lexer::lex_character() -> Token
{
    ASSERT(m_source.consume("'"), "character literal must begin with '");

    const auto location  = m_source.location();
    const auto character = m_source.consume_escape_char();

    return m_source.consume("'")
         ? Token(Token::Type::Character, location, { character, 0x00 })
         : Token(Token::Type::Error,     location, "unterminated character literal");
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
