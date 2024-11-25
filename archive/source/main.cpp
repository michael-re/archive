#include <format>
#include <iostream>

#include "archive/archive.hpp"

auto main() -> int
{
    std::cout << std::format("hello archive!!!!") << std::endl;
    return archive::exit_code::success;
}
