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
         : Token(Token::Type::Unknown,   location);
}

auto Lexer::lex_whitespace() -> std::optional<char>
{
    return std::optional<char>();
}
