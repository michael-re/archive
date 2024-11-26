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
        [[nodiscard]] auto lex_whitespace() -> std::optional<char>;

    private:
        Source m_source;
    };
} // namespace archive::frontend

#endif // ARCHIVE_FRONTEND_LEXER_HPP
