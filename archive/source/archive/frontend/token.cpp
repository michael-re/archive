#include "archive/frontend/token.hpp"

using namespace archive;
using namespace archive::frontend;

Token::Token()
    : Token(Type::Unknown)
{
}

Token::Token(Type type)
    : Token(type, { 1, 1 })
{
}

Token::Token(Type type, Location location)
    : Token(type, location, "")
{
}

Token::Token(Type type, Location location, std::string lexeme)
    : m_type    (type),
      m_location(location),
      m_lexeme  (std::move(lexeme))
{
}

auto Token::type() const -> Type
{
    return m_type;
}

auto Token::location() const -> const Location&
{
    return m_location;
}

auto Token::lexeme() const -> const std::string&
{
    return m_lexeme;
}

auto Token::operator==(const Type type) const -> bool
{
    return m_type == type;
}

auto Token::operator!=(const Type type) const -> bool
{
    return m_type != type;
}
