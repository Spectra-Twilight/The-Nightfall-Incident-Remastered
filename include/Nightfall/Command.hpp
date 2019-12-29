#ifndef NIGHTFALL_COMMAND_HPP
#define NIGHTFALL_COMMAND_HPP

#include <cstdint>
#include <string>

namespace nightfall
{
    class Command
    {   //=================================================================================================================================================
        public:

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Set of classes for reading, writing, and modifying Command Data.
        */
        class Data
        {
            class Interface; // Nightfall/Command_Data/Interface.hpp
            class Reader; // Nightfall/Command_Data/Reader.hpp
            class Writer; // Nightfall/Command_Data/Writer.hpp
            class Editor; // Nightfall/Command_Data/Editor.hpp
        };

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Represents what effects a Command can have on the program that it is targeting.
        */
        enum class Effect
        {
            ModifySize, // Increases (grow) or decreases (damage) a program's current size. Current size may not exceed max.
            ModifyMaxSize,  // Increases or decreases a program's maximum size. Does not affect current size.
            ModifySpeed, // Increases or decreases a program's speed.
            ModifySector // Adds or removes Sectors from the Grid.
        };

        //=================================================================================================================================================
        private:

        std::string name;
        std::string description;

        Effect effect; // What effect does this Command have on its target?
        int8_t strength; // How strong is this Command's effect? Negative values permitted to apply a negative effect.
        uint8_t range; // How many Sectors does this Command reach from its origin point?

        //=================================================================================================================================================
        public:

        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Command(): effect(Effect::ModifySize), strength(0), range(1) {}

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
        inline int8_t getStrength() const { return strength; }
        
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
        inline void setStrength(int8_t newStr) { strength = newStr; }
        
        /*-------------------------------------------------------------------------------------------------------------------------------------------------
            Sets the range of this object's effect.

            Parameter:
            *   newRange: The new range value for this object's effect.
        */
        inline void setRange(uint8_t newRange) { range = newRange; }
        
    };  //=================================================================================================================================================
}

#endif // NIGHTFALL_COMMAND_HPP