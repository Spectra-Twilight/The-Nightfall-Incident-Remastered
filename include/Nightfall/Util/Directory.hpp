#ifndef NIGHTFALL_UTIL_DIRECTORY_HPP
#define NIGHTFALL_UTIL_DIRECTORY_HPP

////////////////////////////////////////////////////////////////////////////////
/// Standard Library Includes
////////////////////////////////////////////////////////////////////////////////
#include <string>

namespace nightfall::util
{
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines all asset file directories in a single location.
    ////////////////////////////////////////////////////////////////////////////
    class Directory
    {
    public:
        Directory() = delete;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filepath of the Commands data file.
        ///
        /// \return A string representation of the Commands data file filepath.
        ////////////////////////////////////////////////////////////////////////
        static std::string commands();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filepath of the base Program texture.
        ///
        /// \return A string representation of the base Program texture filepath.
        ////////////////////////////////////////////////////////////////////////
        static std::string gfx_program_base();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filepath of the Program error icon.
        ///
        /// \return A string representation of the Program error icon filepath.
        ////////////////////////////////////////////////////////////////////////
        static std::string gfx_program_error();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filepath of the default Sector texture.
        ///
        /// \return A string representation of the default Sector texture filepath.
        ////////////////////////////////////////////////////////////////////////
        static std::string gfx_sector_default();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filepath of the Programs data file.
        ///
        /// \return A string representation of the Programs data file filepath.
        ////////////////////////////////////////////////////////////////////////
        static std::string programs();

    private:
        static constexpr std::string_view _data = "data/"; ///< Base data directory. All non-code assets exist within this directory.

        // Folders within "data/"
        static constexpr std::string_view _font = "font/"; ///< Folder containing all fonts used by the game.
        static constexpr std::string_view _gfx = "gfx/"; ///< Folder containing all textures used by the game.

        // Files within "data/"
        static constexpr std::string_view _commands = "commands.dat"; ///< File containing all Command data used by the game.
        static constexpr std::string_view _programs = "programs.dat"; ///< File containing all Program data used by the game.

        // Folders within "data/gfx/"
        static constexpr std::string_view _gfx_programs = "programs/"; ///< Folder containing all Program icon textures.
        static constexpr std::string_view _gfx_sectors = "sectors/"; ///< Folder containing all Sector textures.

        // Files within "data/gfx/programs"
        static constexpr std::string_view _gfx_programs_base = "base.png"; ///< Texture file for the base Program graphic, before an icon is applied.
        static constexpr std::string_view _gfx_programs_error = "error.png"; ///< Texture file for the error Program icon, used when a Program's intended icon fails to load.

        // Files within "data/gfx/sectors"
        static constexpr std::string_view _gfx_sectors_default = "default.png"; ///< Texture file for the default Sector graphic used if none is specified.
    };
} // namespace nightfall::util

#endif // NIGHTFALL_UTIL_DIRECTORY_HPP