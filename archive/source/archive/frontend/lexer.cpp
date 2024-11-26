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
    while (m_source[0])
    {
        // whitespace - any non printable ascii characters + space (' ')
        if (m_source[0] <= 0x20)
        {
            utility::ignore(m_source++);
            continue;
        }

        // single-line comments
        if (m_source.consume("//"))
        {
            while (m_source[0] && !m_source.consume('\n'))
                utility::ignore(m_source++);
            continue;
        }

        // multi-line comments
        if (m_source.consume("/*"))
        {
            while (m_source[0] && !m_source.consume("*/"))
                utility::ignore(m_source++);
        }

        // non whitespace character
        break;
    }

    return m_source[0];
}
