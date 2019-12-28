#ifndef NIGHTFALL_PROGRAM_FACTORY_HPP
#define NIGHTFALL_PROGRAM_FACTORY_HPP

#include <cstdint>
#include <list>
#include <string>

#include <SFML/Graphics.hpp>

#include <Nightfall/Program.hpp>

namespace nf
{
    class Program::Factory
    {   //=======================================================================================================================
        public:
        class Data // Contains classes for reading, writing, and modifying Program::Factory data.
        {
            class Interface; // Nightfall/Data/Program_Factory_Data/Interface.hpp
            class Reader; // Nightfall/Data/Program_Factory_Data/Reader.hpp
            class Writer; // Nightfall/Data/Program_Factory_Data/Writer.hpp
            class Editor; // Nightfall/Data/Program_Factory_Data/Editor.hpp
        };

        //=======================================================================================================================
        private:

        // Identifying information
        std::string name;
        std::string description;

        // Statistics
        uint8_t maxSize;
        uint8_t moveSpeed;
        std::list<std::string> commandIDs;
        std::list<Command*> commands;

        // Graphics
        std::string gfxID; // Appended to graphics filepath prefix and suffix to acquire desired graphic.
        sf::Texture gfx;
        sf::Color color;

        //=======================================================================================================================
        public:

        /*-----------------------------------------------------------------------------------------------------------------------
            Adds the argument to the list of Commands available to Programs generated from this Factory.

            Parameter:
            *   newCommand: Pointer to the Command to be added.
        */
        inline void addCommand(Command* newCommand) { commands.push_back(newCommand); }

        /*-----------------------------------------------------------------------------------------------------------------------
            Adds the ID contained within the argument string to an internal list of CommandIDs available 
            to Programs generated from this Factory.

            Parameter:
            *   newCommandID: A constant reference to a string containing the new Command ID to add.
        */
        inline void addCommandID(const std::string& newCommandID) { commandIDs.push_back(newCommandID); }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns the graphical RGBA color of this object.

            Returns: A constant reference to this object's sf::Color.
        */
        inline const sf::Color& getColor() const { return color; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns pointers to the Commands that this object possesses.

            Returns: A constant reference to a list of Command pointers.
        */
        inline const std::list<Command*>& getCommands() const { return commands; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns the IDs of the Commands that this object possesses.

            Returns: A constant reference to a list of strings containing Command IDs.
        */
        inline const std::list<std::string>& getCommandIDs() const { return commandIDs; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns the description for this object.

            Returns: A constant reference to a string containing this object's description.
        */
        inline const std::string& getDescription() const { return description; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns this object's currently loaded sf::Texture for its graphical icon.

            Returns: A constant reference to an sf::Texture.
        */
        inline const sf::Texture& getGfx() const { return gfx; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns this object's ID used to locate and load its sf::Textures.

            Returns: A constant reference to a string containing this object's gfxID.
        */
        inline const std::string& getGfxID() const { return gfxID; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns the maximum size of this object (in terms of sectors) before buffs.

            Returns: The value of this object's max size.
        */
        inline uint8_t getMaxSize() const { return maxSize; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns the move speed of this object (in terms of sectors per turn) before buffs.

            Returns: The value of this object's move speed.
        */
        inline uint8_t getMoveSpeed() const { return moveSpeed; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Returns the name of this object.

            Returns: A constant reference to a string containing this object's name.
        */
        inline const std::string& getName() const { return name; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Sets this object's color to the argument color's value.

            Parameters:
            *   newColor: A constant reference to an sf::Color that will be copied to this object's color.
        */
        inline void setColor(const sf::Color& newColor) { color = newColor; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Sets this object's description to the argument string's value.

            Parameter:
            *   newDesc: A constant reference to a string that will be copied to this object's description attribute.
        */
        inline void setDescription(const std::string& newDesc) { description = newDesc; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Sets this object's graphics ID to the ID contained within the argument string.

            Parameter:
            *   newGfxID: A constant reference to a string containing the new graphics ID.
        */
        inline void setGfxID(const std::string& newGfxID) { gfxID = newGfxID; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Sets this object's max size (in terms of sectors) to the argument value.

            Parameter:
            *   newSize: A value to be copied to this object's max size attribute.
        */
        inline void setMaxSize(uint8_t newSize) { maxSize = newSize; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Sets this object's move speed (in terms of sectors per turn) to the argument value.

            Parameter:
            *   newSpeed: A value to be copied to this object's move speed attribute.
        */
        inline void setMoveSpeed(uint8_t newSpeed) { moveSpeed = newSpeed; }

        /*-----------------------------------------------------------------------------------------------------------------------
            Sets this object's name to the argument string's value.

            Parameter:
            *   newName: A constant reference to a string that will be copied to this object's name attribute.
        */
        inline void setName(const std::string& newName) { name = newName; }

    };  //=======================================================================================================================
}

#endif // NIGHTFALL_PROGRAM_FACTORY_HPP