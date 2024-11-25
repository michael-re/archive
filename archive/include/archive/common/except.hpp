#pragma once

#ifndef ARCHIVE_COMMON_EXCEPT_HPP
#define ARCHIVE_COMMON_EXCEPT_HPP

#include <string>
#include <exception>

namespace archive
{
    class Exception : public std::exception
    {
    public:
        explicit Exception(std::string message = "") noexcept;
        virtual ~Exception() noexcept;

        [[nodiscard]] virtual auto what()    const noexcept -> const char* override final;
        [[nodiscard]] virtual auto message() const noexcept -> const std::string& final;

    protected:
        std::string m_message;
    };
} // namespace archive

#endif // ARCHIVE_COMMON_EXCEPT_HPP
