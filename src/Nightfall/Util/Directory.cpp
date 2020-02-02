////////////////////////////////////////////////////////////////////////////////
/// Standard Library Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////
/// Nightfall Includes
////////////////////////////////////////////////////////////////////////////////
#include <Nightfall/Util/Directory.hpp>

namespace nightfall::util
{
    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::command_data()
    {
        constexpr uint16_t size = _data.size() + _commands.size();

        std::string filepath;
        filepath.reserve(size);

        (filepath = _data)
            += _commands;

        return filepath;
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::gfx_program_base()
    {
        constexpr uint16_t size = 
            _data.size() + _gfx.size() + _gfx_programs.size() + _gfx_programs_base.size();

        std::string filepath;
        filepath.reserve(size);

        (((filepath = _data)
            += _gfx)
            += _gfx_programs)
            += _gfx_programs_base;

        return filepath;
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::gfx_program_error()
    {
        constexpr uint16_t size =
            _data.size() + _gfx.size() + _gfx_programs.size() + _gfx_programs_error.size();

        std::string filepath;
        filepath.reserve(size);

        (((filepath = _data)
            += _gfx)
            += _gfx_programs)
            += _gfx_programs_error;

        return filepath;
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::gfx_sector_default()
    {
        constexpr uint16_t size = 
            _data.size() + _gfx.size() + _gfx_sectors.size() + _gfx_sectors_default.size();

        std::string filepath;
        filepath.reserve(size);

        (((filepath = _data)
            += _gfx)
            += _gfx_sectors)
            += _gfx_sectors_default;

        return filepath;
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string Directory::program_data()
    {
        constexpr uint16_t size = _data.size() + _programs.size();

        std::string filepath;
        filepath.reserve(size);

        (filepath = _data)
            += _programs;

        return filepath;
    }
} // namespace nightfall::util