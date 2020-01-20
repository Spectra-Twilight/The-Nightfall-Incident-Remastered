////////////////////////////////////////////////////////////////////////////////
/// Nightfall Includes
////////////////////////////////////////////////////////////////////////////////
#include <Nightfall/Util/Directory.hpp>

namespace nightfall::util
{
    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::commands()
    {
        return std::string(_data)
            += _commands;
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::gfx_program_base()
    {
        return ((std::string(_data)
            += _gfx)
            += _gfx_programs)
            += _gfx_programs_base;
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::gfx_program_error()
    {
        return ((std::string(_data)
            += _gfx)
            += _gfx_programs)
            += _gfx_programs_error;
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::gfx_sector_default()
    {
        return ((std::string(_data)
            += _gfx)
            += _gfx_sectors)
            += _gfx_sectors_default;
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::programs()
    {
        return std::string(_data)
            += _programs;
    }
} // namespace nightfall::util