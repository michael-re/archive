#pragma once

#ifndef ARCHIVE_FRONTEND_TOKEN_HPP
#define ARCHIVE_FRONTEND_TOKEN_HPP

#include <string>
#include <cstddef>
#include <cstdint>

#include "archive/frontend/location.hpp"

namespace archive::frontend
{
    class Token final
    {
    public:
        enum class Type;

    public:
        Token();
        Token(Type type);
        Token(Type type, Location location);
        Token(Type type, Location location, std::string lexeme);

        [[nodiscard]] auto type()     const -> Type;
        [[nodiscard]] auto location() const -> const Location&;
        [[nodiscard]] auto lexeme()   const -> const std::string&;

        [[nodiscard]] auto operator==(const Type) const -> bool;
        [[nodiscard]] auto operator!=(const Type) const -> bool;

    private:
        Type        m_type;
        Location    m_location;
        std::string m_lexeme;
    };

    enum class Token::Type
    {
        // punctuation/operators
        Ampersand,    // &
        Ampersand2,   // &&
        Arrow,        // ->
        Bang,         // !
        BangEqual,    // !=
        BraceLeft,    // {
        BraceRight,   // }
        BracketLeft,  // [
        BracketRight, // ]
        Colon,        // :
        Colon2,       // ::
        Comma,        // ,
        Dot,          // .
        Equal,        // =
        Equal2,       // ==
        Greater,      // >
        GreaterEqual, // >=
        Less,         // <
        LessEqual,    // <=
        Minus,        // -
        ParenLeft,    // (
        ParenRight,   // )
        Percent,      // %
        Plus,         // +
        Question,     // ?
        Semicolon,    // ;
        Slash,        // /
        Star,         // *
        VerticalBar,  // |
        VerticalBar2, // ||

        // literals/identifier
        Identifier,
        CharacterLiteral,
        FloatLiteral,
        StringLiteral,
        IntegerLiteral,

        // keywords
        Class,
        Else,
        For,
        Fun,
        If,
        Import,
        Lambda,
        Let,
        Module,
        Nil,
        Return,
        True,
        Var,
        While,

        // basic data types
        Bool,
        Byte,
        Char,
        Void,

        // signed integer types
        I8,
        I16,
        I32,
        I64,
        I128,
        Isize,

        // unsigned integer types
        U8,
        U16,
        U32,
        U64,
        U128,
        Usize,

        // floating point types
        F16,
        F32,
        F64,
        F80,
        F128,

        // for internal use only
        Unknown,
        Error,
        Empty,
        EndOfFile,
    };
} // namespace archive::frontend

#endif // ARCHIVE_FRONTEND_TOKEN_HPP
