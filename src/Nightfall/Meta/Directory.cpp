////////////////////////////////////////////////////////////////////////////////
/// Nightfall Includes
////////////////////////////////////////////////////////////////////////////////
#include <Nightfall/Meta/Directory.hpp>

namespace nightfall::meta
{
    ////////////////////////////////////////////////////////////////////////////
    constexpr std::string Directory::commands()
    {
        return std::string(_data)
            += _commands;
    }

    ////////////////////////////////////////////////////////////////////////////
    constexpr std::string Directory::gfx_program_base()
    {
        return ((std::string(_data)
            += _gfx)
            += _gfx_programs)
            += _gfx_programs_base;
    }

    ////////////////////////////////////////////////////////////////////////////
    constexpr std::string Directory::gfx_program_error()
    {
        return ((std::string(_data)
            += _gfx)
            += _gfx_programs)
            += _gfx_programs_error;
    }

    ////////////////////////////////////////////////////////////////////////////
    constexpr std::string Directory::gfx_sector_default()
    {
        return ((std::string(_data)
            += _gfx)
            += _gfx_sectors)
            += _gfx_sectors_default;
    }

    ////////////////////////////////////////////////////////////////////////////
    constexpr std::string Directory::programs()
    {
        return std::string(_data)
            += _programs;
    }
} // namespace nightfall::meta