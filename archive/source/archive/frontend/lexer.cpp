#include <unordered_map>

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
    const auto current   = lex_whitespace();
    const auto location  = m_source.location();
    if (!current)
        return { Token::Type::EndOfFile, location };

    const auto character = *current;
    if (utility::is_squote(character)) return lex_character();
    if (utility::is_dquote(character)) return lex_string();
    if (utility::is_digit (character)) return lex_number();
    if (utility::is_alpha (character)) return lex_identifier();

    utility::ignore(m_source++);
    return { Token::Type::Error, location, "unexpected character" };
}

auto Lexer::lex_identifier() -> Token
{
    static const auto keywords_types = std::unordered_map<std::string_view, Token::Type>
    {
        { "class",  Token::Type::Class  },
        { "else",   Token::Type::Else   },
        { "for",    Token::Type::For    },
        { "fun",    Token::Type::Fun    },
        { "if ",    Token::Type::If     },
        { "import", Token::Type::Import },
        { "lambda", Token::Type::Lambda },
        { "let",    Token::Type::Let    },
        { "module", Token::Type::Module },
        { "nil",    Token::Type::Nil    },
        { "return", Token::Type::Return },
        { "true",   Token::Type::True   },
        { "var",    Token::Type::Var    },
        { "while",  Token::Type::While  },

        { "bool",   Token::Type::Bool   },
        { "byte",   Token::Type::Byte   },
        { "char",   Token::Type::Char   },
        { "void",   Token::Type::Void   },

        { "i8 ",    Token::Type::I8     },
        { "i16",    Token::Type::I16    },
        { "i32",    Token::Type::I32    },
        { "i64",    Token::Type::I64    },
        { "i128",   Token::Type::I128   },
        { "isize",  Token::Type::Isize  },

        { "u8 ",    Token::Type::U8     },
        { "u16",    Token::Type::U16    },
        { "u32",    Token::Type::U32    },
        { "u64",    Token::Type::U64    },
        { "u128",   Token::Type::U128   },
        { "usize",  Token::Type::Usize  },

        { "f16",    Token::Type::F16    },
        { "f32",    Token::Type::F32    },
        { "f64",    Token::Type::F64    },
        { "f80",    Token::Type::F80    },
        { "f128",   Token::Type::F128   },
    };

    const auto location = m_source.location();
    const auto is_alpha = !m_source.is_at_end() && utility::is_alpha(*m_source.peek());
    ASSERT(is_alpha, "identifier must begin with an alpha character");

    auto lexeme = std::string();
    while (!m_source.is_at_end() && utility::is_alpha(*m_source.peek()))
        lexeme += *(m_source++);

    const auto type = keywords_types.contains(lexeme)
                        ? keywords_types.at(lexeme)
                        : Token::Type::Identifier;
    return { type, location, std::move(lexeme) };
}

auto Lexer::lex_character() -> Token
{
    ASSERT(m_source.consume("'"), "character literal must begin with `'`");

    const auto location  = m_source.location();
    const auto character = m_source.consume_escape_char();

    return m_source.consume("'")
         ? Token(Token::Type::CharacterLiteral, location, { character, 0x00 })
         : Token(Token::Type::Error,            location, "unterminated character literal");
}

auto Lexer::lex_string() -> Token
{
    ASSERT(m_source.consume('"'), "string literal must begin with `\"`");

    auto location = m_source.location();
    auto lexeme   = std::string();

    while (!m_source.is_at_end() && !m_source.peek('"'))
        lexeme += m_source.consume_escape_char();

    return m_source.consume('"')
         ? Token(Token::Type::StringLiteral, location, std::move(lexeme))
         : Token(Token::Type::Error,         location, "unterminated string literal");
}

auto Lexer::lex_number() -> Token
{
    if (m_source.peek("0b") || m_source.peek("0B")) return lex_binnum();
    if (m_source.peek("0x") || m_source.peek("0X")) return lex_hexnum();
    return lex_decnum();
}

auto Lexer::lex_binnum() -> Token
{
    const auto location  = m_source.location();
    const auto is_binary = m_source.consume("0b") || m_source.consume("0B");
    ASSERT(is_binary, "binary literal must begin with `0b` or `0B`");

    auto lexeme = std::string();
    while (m_source.peek('0') || m_source.peek('1') || m_source.peek('_'))
        if (const auto c = m_source.consume(); c != '_') lexeme += utility::to_lower<char>(*c);

    if (lexeme.empty())        return { Token::Type::Error, location, "binary literal must have at least one valid digit" };
    if (lexeme.length() > 128) return { Token::Type::Error, location, "binary literal too large" };

    return { Token::Type::IntegerLiteral, location, "0b" + lexeme };
}

auto Lexer::lex_decnum() -> Token
{
    const auto location   = m_source.location();
    const auto is_decimal = !m_source.is_at_end() && utility::is_digit(*m_source.peek());
    ASSERT(is_decimal, "decimal literal must begin with with `0` - `9`");

    // extract digits from source - returns the number of valid digits read
    const auto read_digits = [this](std::string& lexeme) -> std::size_t
    {
        const auto old = lexeme.length();
        for (auto c = m_source.peek(); c; c = ++m_source)
        {
            if (c == '_')               continue;
            if (!utility::is_digit(*c)) break;
            lexeme += *c;
        }

        return lexeme.length() - old;
    };

    auto lexeme = std::string();
    auto type   = Token::Type::IntegerLiteral;

    // integer
    if (read_digits(lexeme) && m_source.consume('.'))
    {
        type    = Token::Type::FloatLiteral;
        lexeme += '.';

        // fraction
        if (!read_digits(lexeme))
            lexeme += '0';
    }

    // scientific notation
    if (m_source.consume('e') || m_source.consume('E'))
    {
        type = Token::Type::FloatLiteral;
        if      (m_source.consume('+')) lexeme += "e+";
        else if (m_source.consume('-')) lexeme += "e-";
        else                            lexeme += "e+";

        if (!read_digits(lexeme))
        {
            lexeme = "decimal floating pointer number missing exponent value";
            type   = Token::Type::Error;
        }
    }

    return { type, location, std::move(lexeme) };
}

auto Lexer::lex_hexnum() -> Token
{
    const auto location  = m_source.location();
    const auto is_binary = m_source.consume("0x") || m_source.consume("0X");
    ASSERT(is_binary, "hex literal must begin with `0x` or `0X`");

    auto lexeme = std::string();
    while (!m_source.is_at_end())
    {
        if (m_source.consume('_')) continue;
        const auto c = *m_source.peek();
        if (!utility::is_hex_digit(c)) break;

        utility::ignore(m_source++);
        lexeme += c;
    }

    if (lexeme.empty())       return { Token::Type::Error, location, "hex literal must have at least one valid digit" };
    if (lexeme.length() > 32) return { Token::Type::Error, location, "hex literal too large" };

    return { Token::Type::IntegerLiteral, location, "0x" + lexeme };
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
