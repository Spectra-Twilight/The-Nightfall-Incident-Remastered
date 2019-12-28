#ifndef NIGHTFALL_GRID_HPP
#define NIGHTFALL_GRID_HPP

#include <array>
#include <cstdint>
#include <list>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Nightfall/GridSector.hpp>
#include <Nightfall/Program.hpp>

namespace nf
{
    class Grid: public sf::Drawable
    {   //==========================================================================================================================================
        public:
        
        constexpr static uint8_t SectorWidth = 16;
        constexpr static uint8_t SectorHeight = 11;
        constexpr static uint8_t SectorGap = 8; // Gap between adjacent sectors, measured in pixels.

        //==========================================================================================================================================
        private:

        GridSector sectors[SectorHeight][SectorWidth];

        // Programs in play.
        std::list<Program> agentPrograms; // Player's programs.
        std::list<Program> securityPrograms; // Enemy programs.

        // Input data.
        GridSector* pressedSector; // Sector pressed down by mouse1. If mouse1 releases on this Sector, then it is selected.
        sf::Vector2u pressedCoordinates; // Grid position of pressed sectors.

        //==========================================================================================================================================
        public:
        /*------------------------------------------------------------------------------------------------------------------------------------------
            Constructs a Grid of Sectors, without an initialized position.
        */
        inline Grid(): pressedSector(nullptr) {}

        /*------------------------------------------------------------------------------------------------------------------------------------------
            Draw the object to the render target.

            Inherited from sf::Drawable

            Parameters:
            *   target: Render target to draw to.
            *   states: Current render states.
        */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        /*------------------------------------------------------------------------------------------------------------------------------------------
            Returns the position of the grid, which is equivalent to its top-leftmost Sector's
            top-leftmost pixel's position.

            Returns: The Grid's position in the window.
        */
        inline const sf::Vector2f& getPosition() const { return sectors[0][0].getPosition(); }

        /*------------------------------------------------------------------------------------------------------------------------------------------
            Notifies the Grid of a mouse button press, which it then determines 
            if it is relevant or not using the event data and acts accordingly.

            Parameter:
            *   event: A mouse button press event.
            
            Returns: True if the mouse button was pressed on the grid, or false otherwise.
        */
        bool onMouseButtonPressed(const sf::Event& event);

        /*------------------------------------------------------------------------------------------------------------------------------------------
            Notifies the object of a mouse button release, which it then reacts to 
            appropriately.

            Parameter:
            *   event: A mouse button event.
            
            Returns: True if the mouse button was released within the object, or false otherwise.
        */
        bool onMouseButtonReleased(const sf::Event& event);

        /*------------------------------------------------------------------------------------------------------------------------------------------
            Notifies the Grid that the mouse cursor has moved, and provides the event so 
            that the Grid may act further on the details of the event.

            Returns: True if the mouse cursor is inside of the Grid at the time of the call to this event, or false otherwise.
        */
        // bool notifyMouseMovedEvent(sf::Event event);

        /*------------------------------------------------------------------------------------------------------------------------------------------
            Repositions the Grid and all of its owned Sectors, with the top-leftmost Sector's
            top-leftmost pixel at the position specified by the arguments.

            Parameters:
            *   x: The new horizontal position of the grid, relative to the left side of the window.
            *   y: The new vertical position of the grid, relative to the top of the window.
        */
        inline void setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }

        /*------------------------------------------------------------------------------------------------------------------------------------------
            Repositions the Grid and all of its owned Sectors, with the top-leftmost Sector's
            top-leftmost pixel at the position specified by the argument.

            Parameters:
            *   newPos: The new position of the grid.
        */
        void setPosition(sf::Vector2f newPos);

    };  //==========================================================================================================================================
}

#endif // NIGHTFALL_GRID_HPP