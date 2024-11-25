#include <format>
#include <iostream>

#include "archive/archive.hpp"

auto main() -> int
{
    try
    {
        std::cout << std::format("hello archive!!!!") << std::endl;
        return archive::exit_code::success;
    }
    catch (const archive::Exception& e)
    {
        std::cerr << "\n==== caught archive exception ====\n"
                  << e.what()
                  << "\n==== caught archive exception ====\n\n";
        return archive::exit_code::failure;
    }
    catch (const std::exception& e)
    {
        std::cerr << "\n==== caught std exception ====\n"
                  << e.what()
                  << "\n==== caught std exception ====\n\n";
        return archive::exit_code::failure;
    }
    catch (...)
    {
        std::cerr << "\n==== caught unknown exception ===="
                  << "\n==== caught unknown exception ====\n\n";
        return archive::exit_code::failure;
    }
}
