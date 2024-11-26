#pragma once

#ifndef ARCHIVE_FRONTEND_LEXER_HPP
#define ARCHIVE_FRONTEND_LEXER_HPP

#include "archive/frontend/location.hpp"
#include "archive/frontend/source.hpp"
#include "archive/frontend/token.hpp"

namespace archive::frontend
{
    class Lexer final
    {
    public:
        explicit Lexer(std::string source = "");

        [[nodiscard]] auto lex() -> Token;

    private:
        [[nodiscard]] auto lex_identifier() -> Token;
        [[nodiscard]] auto lex_character()  -> Token;
        [[nodiscard]] auto lex_string()     -> Token;
        [[nodiscard]] auto lex_number()     -> Token;
        [[nodiscard]] auto lex_binnum()     -> Token;
        [[nodiscard]] auto lex_decnum()     -> Token;
        [[nodiscard]] auto lex_hexnum()     -> Token;

        [[nodiscard]] auto lex_whitespace()   -> std::optional<char>;
        [[nodiscard]] auto lex_nonprintable() -> bool;
        [[nodiscard]] auto lex_comments()     -> bool;

    private:
        Source m_source;
    };
} // namespace archive::frontend

#endif // ARCHIVE_FRONTEND_LEXER_HPP
