#ifndef SPYBOT_PROGRAM_FACTORY_HPP
#define SPYBOT_PROGRAM_FACTORY_HPP

#include <cstdint>
#include <list>
#include <string>

#include <SFML/Graphics.hpp>

namespace Spybot
{
    class Program_Factory
    {
        //=======================================================================================================================
        private:
        // Identifying information.
        std::string name;
        std::string description;

        // Statistics
        uint8_t maxSize;
        uint8_t moveSpeed;
        std::list<std::string> commands;

        // Graphics
        sf::Texture icon;
        sf::Color primaryColor; // Known as 'color1' in the data files.
        sf::Color secondaryColor; // Known as 'color2' in the data files.

        //=======================================================================================================================
        public:
        //-----------------------------------------------------------------------------------------------------------------------
        // Getter Methods
        inline const std::string& getName() const { return name; }
        inline const std::string& getDescription() const { return description; }

        inline uint8_t getMaxSize() const { return maxSize; }
        inline uint8_t getMoveSpeed() const { return moveSpeed; }
        inline const std::list<std::string>& getCommands() const { return commands; }

        inline const sf::Texture& getIcon() const { return icon; }
        inline const sf::Color& getPrimaryColor() const { return primaryColor; }
        inline const sf::Color& getSecondaryColor() const { return secondaryColor; }
        //-----------------------------------------------------------------------------------------------------------------------
    };
}

#endif // SPYBOT_PROGRAM_FACTORY_HPP