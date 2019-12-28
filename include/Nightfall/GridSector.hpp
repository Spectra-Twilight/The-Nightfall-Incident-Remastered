#ifndef NIGHTFALL_GRID_SECTOR_HPP
#define NIGHTFALL_GRID_SECTOR_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include <Nightfall/Program.hpp>

namespace nf
{
    class Program;

    class GridSector: public sf::Drawable
    {   //======================================================================================================================================
        private:

        // State data.
        const Program* program; // The Program currently occupying this Sector.
        bool active; // Sector is invisible and not enterable if inactive.
        bool linkRight; // Should linkRight be drawn?
        bool linkDown; // Should linkDown be drawn?

        // Graphical data.
        constexpr static unsigned int baseSideLength = 28; // Pixels at scale x1.
        static unsigned int sideLength; // Length of each side, in pixels, of all GridSectors.

        const static std::string defaultGfxDir;
        static sf::Texture defaultGfx;

        const static sf::Color color;
        constexpr static float linkScale = 1.0f / 3.0f; // Link scale compared to the size of a Sector.

        sf::Sprite sectorGfx; // Only drawn if the Sector is not currently occupied by a Program.
        sf::Sprite programGfx;
        sf::Sprite linkRightGfx; // Displayed if this Sector and the adjacent Sector to the right share the same program.
        sf::Sprite linkDownGfx; // Displayed if this Sector and the adjacent Sector below share the same program.

        //======================================================================================================================================
        public:
        /*--------------------------------------------------------------------------------------------------------------------------------------
            Constructs a Sector with the default Sector graphic. The value of the argument 
            determines whether this Sector begins as active or inactive.
            
            An inactive Sector will not be visible on the grid and cannot be entered by Programs.

            Parameter:
            *   isActive: A value of true will instantiate this Sector in an active state, false will start it as inactive.
        */
        inline GridSector(bool isActive = true): GridSector(defaultGfx, isActive) {}

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Constructs a Sector with the specified Sector graphic. The value of the second argument 
            determines whether this Sector begins as active or inactive.

            An inactive Sector will not be visible on the grid and cannot be entered by Programs.

            Parameters:
            *   sectorTexture: The texture to generate the Sector's graphic from.
            *   isActive: A value of true will instantiate this Sector in an active state, false will start it as inactive.
        */
        GridSector(const sf::Texture& sectorTexture, bool isActive = false);

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Draw the object to the render target.

            Inherited from sf::Drawable

            Parameters:
            *   target: Render target to draw to.
            *   states: Current render states.
        */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Returns the position of the top-leftmost pixel of this Sector.

            Returns: The position of this Sector.
        */
        inline const sf::Vector2f& getPosition() const { return sectorGfx.getPosition(); }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Returns the Program currently occupying this Sector.

            Returns: Pointer to the Program at this Sector.
        */
        inline const Program* getProgram() const { return program; }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Retrieves the length of a GridSector's side in pixels, which is consistent across all GridSectors.

            Returns: The length of a GridSector's side.
        */
        inline static unsigned int getSideLength() { return sideLength; }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Returns the active state of this Sector. A Sector that is inactive will not 
            draw any graphics and cannot be entered by Programs.

            Returns: True if this Sector is currently active, or false otherwise.
        */
        inline bool isActive() const { return active; }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Creates a texture from the image stored at an internally stored directory.
            This graphic is used for sectors if none is provided or if a requested 
            alternate sector graphic is unavailable.
            
            Returns: True if the image was successfully loaded, or false otherwise.
        */
        inline static bool loadDefaultSectorGfx() { return defaultGfx.loadFromFile(defaultGfxDir); }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Notifies the GridSectors of mouse movement, and provides the details of the event 
            for the GridSector to potentially act upon.

            Returns: True if the mouse cursor is inside of the GridSector at the time of the call to this function, or false otherwise.
        */
        bool notifyMouseMovedEvent(sf::Event event);

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Sets the active state of the Sector.
            An inactive Sector will not be drawn and cannot be entered by Programs.

            Parameter:
            *   newState: True will make this Sector active, false will make it inactive.
        */
        inline void setActive(bool newState) { active = newState; }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Indicates to this Sector whether or not is should draw a graphical link 
            to the Sector below it.

            This should be activated when this Sector and the Sector below it are occupied
            by the same Program.

            Parameter:
            *   isLinkDown: If true, this Sector will draw a linking graphic to the Sector below it.
                            If false, then the link will not be drawn.
        */
        inline void setLinkDown(bool isLinkDown) { linkDown = isLinkDown; }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Indicates to this Sector whether or not is should draw a graphical link 
            to the Sector to its right.

            This should be activated when this Sector and the Sector to its right are occupied
            by the same Program.

            Parameter:
            *   isLinkRight: If true, this Sector will draw a linking graphic to the Sector to its right.
                             If false, then the link will not be drawn.
        */
        inline void setLinkRight(bool isLinkRight) { linkRight = isLinkRight; }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Repositions the Sector to the position specified by the arguments.

            Parameter:
            *   x: The new horizontal position of the Sector.
            *   y: The new vertical position of the Sector.
        */
        inline void setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Repositions the Sector to the position specified by the argument.

            Parameter:
            *   pos: The Sector's new position.
        */
        void setPosition(const sf::Vector2f& pos);

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Assigns a new Program to occupy this Sector.

            Parameter:
            *   newProgram: Pointer to the Program that will now occupy this Sector.
        */
        void setProgram(const Program* newProgram);

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Sets the scale for the length of GridSector sides (in pixels), which is shared 
            between all GridSectors. The value of the new scale is multiplied by the base 
            side length for GridSectors.

            Parameter:
            *   newSideLengthScale: The new scale to be multiplied against the base side length.
        */
        inline static void setSideLengthScale(unsigned int newSideLengthScale) { sideLength = newSideLengthScale * baseSideLength; }

    };  //======================================================================================================================================
}

#endif // NIGHTFALL_GRID_SECTOR_HPP