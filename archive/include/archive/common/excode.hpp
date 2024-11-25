#pragma once

#ifndef ARCHIVE_COMMON_EXCODE_HPP
#define ARCHIVE_COMMON_EXCODE_HPP

namespace archive::exit_code
{
    inline constexpr auto success       =  0; //* successful execution of program
    inline constexpr auto failure       =  1; //* unsuccessful execution of program
    inline constexpr auto usage         = 64; //* command line usage error
    inline constexpr auto data_error    = 65; //* data format error
    inline constexpr auto no_input      = 66; //* cannot open input
    inline constexpr auto no_user       = 67; //* addressee unknown
    inline constexpr auto no_host       = 68; //* host name unknown
    inline constexpr auto unavailable   = 69; //* service unavailable
    inline constexpr auto software      = 70; //* internal software error
    inline constexpr auto os_error      = 71; //* system error (e.g., can't fork)
    inline constexpr auto os_file       = 72; //* critical os file missing
    inline constexpr auto cant_create   = 73; //* can't create (user) output file
    inline constexpr auto io_error      = 74; //* input/output error
    inline constexpr auto temp_fail     = 75; //* temp failure; user is invited to retry
    inline constexpr auto protocol      = 76; //* remote error in protocol
    inline constexpr auto no_permission = 77; //* permission denied
    inline constexpr auto config        = 78; //* configuration error
} // namespace archive::exit_code

#endif // ARCHIVE_COMMON_EXCODE_HPP
