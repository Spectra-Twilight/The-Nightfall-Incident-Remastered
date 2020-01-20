#ifndef NIGHTFALL_PROGRAM_FACTORY_HPP
#define NIGHTFALL_PROGRAM_FACTORY_HPP

////////////////////////////////////////////////////////////////////////////////
/// Standard Library Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <list>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// Nightfall Includes
////////////////////////////////////////////////////////////////////////////////
#include <Nightfall/Program.hpp>

////////////////////////////////////////////////////////////////////////////////
/// SFML Includes
////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

namespace nightfall
{
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines a type of Program, which can be used to create multiple Program instances.
    ////////////////////////////////////////////////////////////////////////////
    class Program::Factory
    {   
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the RGBA color for this Program Factory.
        ///
        /// \return The RGBA color of this Program Factory.
        ////////////////////////////////////////////////////////////////////////
        const sf::Color& color() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the RGBA color value of this Program Factory to the argument.
        ///
        /// \param color The new color for this Program Factory.
        ////////////////////////////////////////////////////////////////////////
        void color(const sf::Color& color);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the description of the Program constructed by this Factory.
        ///
        /// \return The description of the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        const std::string& description() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Set the description for the Program constructed by this Factory to the argument.
        ///
        /// \param desc The new description for the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        void description(const std::string& desc);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Set the icon ID for the Program constructed by this Factory to the argument.
        ///
        /// Invoking this function will NOT load the new icon indicated by the 
        /// new ID. In order to do so, icon_reload() should be called after this 
        /// function returns.
        ///
        /// \param id The new icon ID for the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        void icon_id(const std::string& id);
        
        ////////////////////////////////////////////////////////////////////////
        /// \brief Reload the icon of the Program constructed by this Factory.
        ///
        /// This function should be called after a new icon is set with icon_id()
        /// or after a change in the global graphics quality in order for the 
        /// new setting to take effect.
        ///
        /// The icon loaded will depend both on this Factory's internal icon_id, 
        /// as well as the global graphics settings.
        ///
        /// If this function fails to load the desired icon_id, then this 
        /// Factory's icon will be set to the global error graphic and this 
        /// function returns false.
        ///
        /// \return True if the desired icon was successfully loaded, or false otherwise.
        ////////////////////////////////////////////////////////////////////////
        bool icon_reload();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the base maximum size of the Program constructed by this Factory.
        ///
        /// A Program's maximum size defines how many Sectors it may occupy 
        /// simultaneously before it must vacate the Sector it began occupying
        /// the least recently.
        ///
        /// \return The base maximum size of the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        uint8_t max_size() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the base maximum size of the Program constructed by this Factory to the argument.
        ///
        /// A Program's maximum size defines how many Sectors it may occupy 
        /// simultaneously before it must vacate the Sector it began occupying
        /// the least recently.
        ///
        /// \param max_size The new base maximum size for the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        void max_size(uint8_t max_size);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the base move speed of the Program constructed by this Factory.
        ///
        /// A Program's move speed defines the maximum number of Sectors it may 
        /// traverse in a single turn.
        ///
        /// \return The base move speed of the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        uint8_t move_speed() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the base move speed of the Program constructed by this Factory to the argument.
        ///
        /// A Program's move speed defines the maximum number of Sectors it may 
        /// traverse in a single turn.
        ///
        /// \param move_speed The new base move speed of the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        void move_speed(uint8_t move_speed);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the name of the Program constructed by this Factory.
        ///
        /// \return The name of the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        const std::string& name() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the name of the Program constructed by this Factory to the argument.
        ///
        /// \param name The new name of the Program constructed by this Factory.
        ////////////////////////////////////////////////////////////////////////
        void name(const std::string& name);

    private:
        ////////////////////////////////////////////////////////////////////////
        /// Instance Members
        ////////////////////////////////////////////////////////////////////////
        std::string _name; ///< Name of the Program constructed by this Factory.
        std::string _desc; ///< Description of the Program constructed by this Factory.

        uint8_t _max_size; ///< Number of Sectors the Program can occupy at once, before modification.
        uint8_t _move_speed; ///< Number of Sectors the Program can traverse in one turn, before modification.

        std::string _icon_id; ///< Filename (without suffix) that identifies the Program's icon texture file.
        sf::Texture _icon; ///< The texture for this Program type's icon.
        sf::Color _color; ///< Color of the Program's base sprite.
    };
} // namespace nightfall

#endif // NIGHTFALL_PROGRAM_FACTORY_HPP