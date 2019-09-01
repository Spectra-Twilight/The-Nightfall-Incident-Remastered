#ifndef SPYBOT_COMMAND_HPP
#define SPYBOT_COMMAND_HPP

#include <cstdint>
#include <string>

namespace Spybot
{
    class Command
    {   //=================================================================================================================================================
        public:

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Set of classes for reading, writing, and modifying Command Data.
        */
        class Data
        {
            class Interface; // Spybot/Command_Data/Interface.hpp
            class Reader; // Spybot/Command_Data/Reader.hpp
            class Writer; // Spybot/Command_Data/Writer.hpp
            class Editor; // Spybot/Command_Data/Editor.hpp
        };

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Represents what effects a Command can have on the program that it is targeting.
        */
        enum class Effect
        {
            Damage, // Subtracts existing Sectors from the target program, potentially deleting it.
            Growth, // Adds Sectors to the target program, but not exceeding its maximum size.
            MaxSizeUp, // Increases the maximum (though not the current) size of the target program.
            MaxSpeedUp, // Increases the maximum speed of the target program.
            MaxSpeedDown // Decreases the maximum speed of the target program.
        };

        //=================================================================================================================================================
        private:

        std::string name;
        std::string description;

        Effect effect; // What effect does this Command have on its target?
        uint8_t strength; // How strong is this Command's effect?
        uint8_t range; // How many Sectors does this Command reach from its origin point?

        //=================================================================================================================================================
        public:

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Command(): effect(Effect::Damage), strength(0), range(1) {}

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Retrieves this object's description.

            Returns: A constant reference to a string containing the object's description.
        */
        inline const std::string& getDescription() const { return description; }

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Retrieves this object's effect.

            Returns: The value of the effect of this object.
        */
        inline Effect getEffect() const { return effect; }

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Retrieves this object's name.

            Returns: A constant reference to a string containing this object's name.
        */
        inline const std::string& getName() const { return name; }

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Retrieves this object's effect's strength.

            Returns: The value of the strength of this object's effect.
        */
        inline uint8_t getStrength() const { return strength; }
        
        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Retrieves this object's effect's range.

            Returns: The value of the range of this object's effect.
        */
        inline uint8_t getRange() const { return range; }
        
        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Sets the description of this object to the provided argument.

            Parameter:
            *   newDesc: A constant reference to a string containing the new description for this object.
        */
        inline void setDescription(const std::string& newDesc) { description = newDesc; }

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Sets the effect of this object to the provided argument.

            Parameter:
            *   newEffect: The value of the new effect that this object will have.
        */
        inline void setEffect(Effect newEffect) { effect = newEffect; }
        
        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Sets the name of this object to the provided argument.

            Parameter:
            *   newName: A constant reference to a string containing this object's new name.
        */
        inline void setName(const std::string& newName) { name = newName; }
        
        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Sets the strength of this object's effect.

            Parameter:
            *   newStr: The new strength value for this object's effect.
        */
        inline void setStrength(uint8_t newStr) { strength = newStr; }
        
        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Sets the range of this object's effect.

            Parameter:
            *   newRange: The new range value for this object's effect.
        */
        inline void setRange(uint8_t newRange) { range = newRange; }
        
    };  //=================================================================================================================================================
}

#endif // SPYBOT_COMMAND_HPP