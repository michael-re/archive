#include <format>

#include "archive/common/fatal.hpp"

using namespace archive;

Fatal::Fatal(const std::string_view     message,
             const std::source_location location) noexcept
    : Exception()
{
    try
    {
        auto formatted = std::format("fatal error: {}:{}:{}\n", location.file_name(), location.line(), location.column())
                       + std::format(" * location: {}:{}\n",    location.line(), location.column())
                       + std::format(" * function: {}",         location.function_name());

        if (!message.empty())
        {
            formatted += "\n |";
            formatted += "\n | ";

            // insert message
            for (const auto& c : message)
            {
                formatted += c;
                if (c == '\n')
                    formatted += " | ";
            }

            formatted += "\n |";
        }

        // successfully created formatted error message
        this->m_message = std::move(formatted);
    }
    catch (...)
    {
        // something went wrong!!!
        this->m_message.clear();
    }
}
