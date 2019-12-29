#ifndef NIGHTFALL_PROGRAM_HPP
#define NIGHTFALL_PROGRAM_HPP

#include <list>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include <Nightfall/Command.hpp>
#include <Nightfall/GridSector.hpp>

#include <Trie/trie.hpp>

namespace nightfall
{
    class GridSector;

    class Program: public sf::Drawable
    {   //============================================================================================================================================
        public:
        class Factory; // Program_Factory.hpp

        constexpr static uint8_t baseGfxEdge = 6; // Size of the baseGfx's "edge", in pixels.

        //============================================================================================================================================
        private:
        const static std::string BaseGfxDir;
        static sf::Texture baseGfx; // All programs use the same base texture before applying their unique icons.

        // Attributes
        // A program's name, description, and commands will never change, and can be retrieved from the factory which created it.
        // Size and speed can be modified by buffs during gameplay, and thus personal copies are made.
        const Factory* factory;
        std::list<GridSector*> sectors;
        uint8_t maxSize;
        uint8_t speed;

        // Graphics
        sf::Sprite icon;

        //============================================================================================================================================
        public:
        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Constructs a Program with the attributes matching that of the Program_Factory used to construct it.

            Note that this constructor does NOT link the created Program to its available commands.
            Commands must be linked manually by using the addCommand() function.

            Parameters:
            *   baseProgram: The Program_Factory which this Program will be constructed to replicate.
        */
        Program(const Factory* baseProgram);

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Adds the argument Grid Sector into the front of an internal list of Sectors ordered 
            from newest to oldest. Adding a Newest Sector will make it the last Sector to be deleted 
            in the case of an attack on the Program.

            If the provided Sector already exists within the list of Sectors, it will be moved to 
            the front, becoming the newest Sector.

            Parameter:
            *   newSector: Pointer to the sector for this Program to exist upon.
        */
        void addNewestSector(GridSector* newSector);

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Adds the argument Grid Sector into the back of an internal list of Sectors ordered 
            from newest to oldest. Add an Oldest Sector will make it the first sector to be deleted 
            in the case of an attack on the Program.

            If the provided Sector already exists within the list of Sectors, it will be moved to 
            the back, becoming the oldest Sector.

            Parameter:
            *   oldSector: Pointer to the sector for this Program to exist upon.
        */
        void addOldestSector(GridSector* oldSector);

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Draw the object to the render target.

            Inherited from sf::Drawable

            Parameters:
            *   target: Render target to draw to.
            *   states: Current render states.
        */
        inline void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(icon); }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns the base graphic used by all Programs.

            Returns: A reference to the Program base texture.
        */
        inline static const sf::Texture& getBaseGfx() { return baseGfx; }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns this Program's Color.

            Returns: The Color of this Program.
        */
        const sf::Color& getColor() const;

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns a list of pointers to the Command objects available to this Program.

            Returns: The Commands of this Program.
        */
        const std::list<Command*>& getCommands() const;

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns this Program's description.

            Returns: A reference to a string of the Program's description.
        */
        const std::string& getDescription() const;

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns this Program's maximum size (how many sectors it can occupy at once before the oldest sector is deleted).

            Returns: The maximum size of the Program.
        */
        inline uint8_t getMaxSize() const { return maxSize; }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns this Program's name.

            Returns: A string of the Program's name.
        */
        const std::string& getName() const;

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Retrieves a pointer to the newest GridSector of this Program.

            If this Program occupies no GridSectors, then this function returns nullptr.

            Returns: Pointer to newest GridSector, or nullptr if none exist.
        */
        GridSector* getNewestSector() const;

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Retrieves a pointer to the oldest GridSector of this Program.

            If this Program occupies no GridSectors, then this function returns nullptr.

            Returns: Pointer to oldest GridSector, or nullptr if none exist.
        */
        GridSector* getOldestSector() const;

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Return this Program's speed (how many sectors it can move in one turn).

            Returns: The speed of the Program.
        */
        inline uint8_t getSpeed() const { return speed; }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns: True if this Program has Sectors belonging to it, or false otherwise.
        */
        inline bool hasSectors() const { return !sectors.empty(); }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Loads the base texture used for all Programs from an internally stored directory.
            
            Returns: True if the image was successfully loaded, or false otherwise.
        */
        inline static bool loadBaseGfx() { return baseGfx.loadFromFile(BaseGfxDir); }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Removes the newest Sector belonging to this Program, and returns it.

            If this Program has no Sectors at the start of the call to this function, 
            then this function returns nullptr and does nothing else.

            Returns: This Program's newest Sector after removing it, or nullptr if this Program had no Sectors.
        */
        GridSector* removeNewestSector();
        
        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Removes the oldest Sector belonging to this Program, and returns it.

            If this Program has no Sectors at the start of the call to this function, 
            then this function returns nullptr and does nothing else.

            Returns: This Program's oldest Sector after removing it, or nullptr if this Program had no Sectors.
        */
        GridSector* removeOldestSector();

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Sets the on-screen coordinate position of the graphic of this Program.
            
            Parameters:
            *   x: The horizontal offset, from the left side of the screen, in pixels.
            *   y: The vertical offset, from the top of the screen, in pixels.
        */
        inline void setGfxPosition(float x, float y) { icon.setPosition(x, y); }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Sets the on-screen coordinate position of the graphic of this Program.
            
            Parameters:
            *   pos: The offset from the top-right corner of the screen in pixels.
        */
        inline void setGfxPosition(const sf::Vector2f& pos) { icon.setPosition(pos); }

    };  //============================================================================================================================================
}

#endif // NIGHTFALL_PROGRAM_HPP