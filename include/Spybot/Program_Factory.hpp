#ifndef SPYBOT_PROGRAM_FACTORY_HPP
#define SPYBOT_PROGRAM_FACTORY_HPP

#include <cstdint>
#include <list>
#include <string>

#include <SFML/Graphics.hpp>

#include <Spybot/DataLoader.hpp>

namespace Spybot
{
    class Program_Factory
    {   //=======================================================================================================================
        private:
        // Placeholder data, in the case that externally provided data is invalid.
        static std::string error_name;
        static std::string error_description;
        const static uint8_t error_maxSize = 1;
        const static uint8_t error_moveSpeed = 0;
        static std::string error_icon;
        static sf::Color error_color;

        //-----------------------------------------------------------------------------------------------------------------------
        // Identifying information.
        std::string name;
        std::string description;

        // Statistics
        uint8_t maxSize;
        uint8_t moveSpeed;
        std::list<std::string> commands;

        // Graphics
        sf::Texture icon;
        sf::Color color;

        //=======================================================================================================================
        public:
        /*-----------------------------------------------------------------------------------------------------------------------
            Constructs a Program_Factory with no defined attributes.
        */
        inline Program_Factory() {}

        /*-----------------------------------------------------------------------------------------------------------------------
            Constructs a Program_Factory defined by the attributes stored within 
            the provided DataLoader at the time of the call to this constructor.

            If the required attributes are not currently available from the DataLoader,
            then substitutions will be made using placeholder values.

            Parameter:
            *   loader: DataLoader with attributes for defining Programs currently loaded.
        */
        inline Program_Factory(const DataLoader& loader) { define(loader); }

        /*-----------------------------------------------------------------------------------------------------------------------
            Defines the attributes of this Program_Factory using the attributes 
            stored within the provided DataLoader at the time of the call.

            If the required attributes are not currently available from the DataLoader,
            then substitutions will be made using placeholder values.

            Parameter:
            *   loader: DataLoader with attributes for defining Programs currently loaded.
        */
        void define(const DataLoader& loader);

        //-----------------------------------------------------------------------------------------------------------------------
        // Getter Methods
        inline const std::string& getName() const { return name; }
        inline const std::string& getDescription() const { return description; }

        inline uint8_t getMaxSize() const { return maxSize; }
        inline uint8_t getMoveSpeed() const { return moveSpeed; }
        inline const std::list<std::string>& getCommands() const { return commands; }

        inline const sf::Texture& getIcon() const { return icon; }
        inline const sf::Color& getColor() const { return color; }
        //-----------------------------------------------------------------------------------------------------------------------
        // Setter Methods
        inline void setName(const std::string& newName) { name = newName; }
        inline void setDescription(const std::string& newDesc) { description = newDesc; }

        inline void setMaxSize(uint8_t newSize) { maxSize = newSize; }
        inline void setMoveSpeed(uint8_t newSpeed) { moveSpeed = newSpeed; }
        inline void addCommand(const std::string& newCommand) { commands.push_back(newCommand); }

        inline bool loadIcon(const std::string& iconFilepath) { return icon.loadFromFile(iconFilepath); }
        inline void setColor(const sf::Color& newPrimaryColor) { color = newPrimaryColor; }
        //-----------------------------------------------------------------------------------------------------------------------
    };  //=======================================================================================================================
}

#endif // SPYBOT_PROGRAM_FACTORY_HPP